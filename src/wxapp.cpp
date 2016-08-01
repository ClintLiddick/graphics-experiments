#include <memory>
#include <stdexcept>
#include <string>
#include <GL/gl3w.h>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/glcanvas.h>

static const char* v_shader =
    "#version 330 core\n"
    "layout (location = 0) in vec3 vp;"
    "void main() {"
    "gl_Position = vec4 (vp, 1.0f);"
    "}";

static const char* f_shader =
    "#version 330 core\n"
    "out vec4 color;"
    "void main() {"
    "color = vec4 (0.5f, 0.0f, 0.5f, 1.0f);"
    "}";

// clang-format off
static const GLfloat points[] = {
    0.0f,  0.5f,  0.0f,
    0.5f, -0.5f,  0.0f,
    -0.5f, -0.5f,  0.0f
};
// clang-format on

class Canvas : public wxGLCanvas
{
public:
  Canvas(wxFrame* parent, const wxGLAttributes& canvas_attrs)
      : wxGLCanvas(parent, canvas_attrs, wxID_ANY, wxDefaultPosition,
                   wxDefaultSize, 0, "GLCanvas")
      , shader_prog(0)
      , vbo(0)
      , vao(0)
  {
    wxGLContextAttrs ctx_attrs;
    ctx_attrs.PlatformDefaults().CoreProfile().OGLVersion(3, 3).EndList();
    gl_context = std::make_unique<wxGLContext>(this, nullptr, &ctx_attrs);
    if (!gl_context->IsOK()) {
      std::cerr << "Failed to initialize OpenGL version 3.3 core" << std::endl;
    }
    SetCurrent(*gl_context);

    if (gl3wInit()) {
      // throw std::runtime_error("Failed to load OpenGL context");
      std::cerr << "Failed to load OpenGL context" << std::endl;
    }

    if (!gl3wIsSupported(3, 3)) {
      // throw std::runtime_error("OpenGL 3.3 not supported");
      std::cerr << "OpenGL 3.3 not supported" << std::endl;
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    // setup shaders
    GLint success;
    GLchar compile_log[512];

    GLuint vs = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vs, 1, &v_shader, NULL);
    glCompileShader(vs);
    glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(vs, 512, NULL, compile_log);
      std::cerr << "ERROR VS: " << compile_log << std::endl;
    }

    GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fs, 1, &f_shader, NULL);
    glCompileShader(fs);
    glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(fs, 512, NULL, compile_log);
      std::cerr << "ERROR FS: " << compile_log << std::endl;
    }

    shader_prog = glCreateProgram();
    glAttachShader(shader_prog, fs);
    glAttachShader(shader_prog, vs);
    glLinkProgram(shader_prog);
    glGetProgramiv(shader_prog, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(shader_prog, 512, NULL, compile_log);
      std::cerr << "ERROR PROG: " << compile_log << std::endl;
    }
    glDeleteShader(vs);
    glDeleteShader(fs);

    // setup vert array objs
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

    glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat),
                            (GLvoid*)0);
        glEnableVertexAttribArray(0);

        // glBindBuffer(GL_ARRAY_BUFFER, 0);  // TODO safe w/ above comment out?
    glBindVertexArray(0);              // unbind vao
  }

  ~Canvas()
  {
    SetCurrent(*gl_context);
    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
  }

  void OnPaint(wxPaintEvent& WXUNUSED(event))
  {
    std::cout << "loop" << std::endl;
    SetCurrent(*gl_context);
    glViewport(0, 0, (GLint)GetSize().x, (GLint)GetSize().y);
    wxPaintDC(this);
    glClearColor(0.15f, 0.15f, 0.15f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(shader_prog);
    if ((err = glGetError()) != GL_NO_ERROR) {
      std::cerr << "OpenGL error using shader: " << err << std::endl;
    }
    glBindVertexArray(vao);
    if ((err = glGetError()) != GL_NO_ERROR) {
      std::cerr << "OpenGL error binding array: " << err << std::endl;
    }
    glDrawArrays(GL_TRIANGLES, 0, 3);
    if ((err = glGetError()) != GL_NO_ERROR) {
      std::cerr << "OpenGL error drawing: " << err << std::endl;
    }
    glBindVertexArray(0);
    // glFlush();
    SwapBuffers();
  }

protected:
  DECLARE_EVENT_TABLE();

private:
  wxGLAttributes gl_attrs;
  std::unique_ptr<wxGLContext> gl_context;
  GLuint shader_prog;
  GLuint vbo;  // vert buffer
  GLuint vao;  // vert array
  GLenum err;
};

// clang-format off
BEGIN_EVENT_TABLE(Canvas, wxGLCanvas)
    EVT_PAINT(Canvas::OnPaint)
END_EVENT_TABLE()
// clang-format on

enum { ID_Hello = 1 };

class Frame : public wxFrame
{
public:
  Frame(const wxString& title, const wxPoint& pos, const wxSize& size)
      : wxFrame(NULL, wxID_ANY, title, pos, size)
  {
    wxMenu* menuFile = new wxMenu();
    menuFile->Append(ID_Hello, "&Hello...\tCtrl-H",
                     "Help string show in status bar");
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);

    wxMenu* menuHelp = new wxMenu();
    menuHelp->Append(wxID_ABOUT);

    wxMenuBar* menuBar = new wxMenuBar();
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");

    SetMenuBar(menuBar);
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
  }

private:
  void OnExit(wxCommandEvent& event) { Close(true); }

  void OnAbout(wxCommandEvent& event)
  {
    wxMessageBox("This is a wxWidgets' Hello world example",
                 "About Hello World", wxOK | wxICON_INFORMATION);
  }

  void OnHello(wxCommandEvent& event)
  {
    wxLogMessage("Hello World from wxWidgets!");
  }

  wxDECLARE_EVENT_TABLE();
};

// clang-format off
wxBEGIN_EVENT_TABLE(Frame, wxFrame)
    EVT_MENU(ID_Hello, Frame::OnHello)
    EVT_MENU(wxID_EXIT, Frame::OnExit)
    EVT_MENU(wxID_ABOUT, Frame::OnAbout)
wxEND_EVENT_TABLE();
// clang-format on

class App : public wxApp
{
public:
  bool OnInit()
  {
    Frame* frame = new Frame("Hello World", wxPoint(50, 50), wxSize(450, 340));
    frame->Show(true);
    wxGLAttributes canvas_attrs;
    canvas_attrs.PlatformDefaults().Defaults().EndList();
    if (!wxGLCanvas::IsDisplaySupported(canvas_attrs)) {
      std::cerr << "Display doesn't support OpenGL attributes" << std::endl;
      return false;
    }
    new Canvas(frame, canvas_attrs);
    return true;
  }
};

wxIMPLEMENT_APP(App);
