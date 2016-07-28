#include <GL/gl3w.h>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif
#include <wx/glcanvas.h>

class App : public wxApp
{
public:
  bool OnInit();
};

class Frame : public wxFrame
{
public:
  Frame(const wxString& title, const wxPoint& pos, const wxSize& size);

private:
  void OnExit(wxCommandEvent& event);
  void OnAbout(wxCommandEvent& event);
  void OnHello(wxCommandEvent& event);

  wxDECLARE_EVENT_TABLE();
};

enum { ID_Hello = 1 };

// clang-format off
wxBEGIN_EVENT_TABLE(Frame, wxFrame)
    EVT_MENU(ID_Hello, Frame::OnHello)
    EVT_MENU(wxID_EXIT, Frame::OnExit)
    EVT_MENU(wxID_ABOUT, Frame::OnAbout)
wxEND_EVENT_TABLE()

wxIMPLEMENT_APP(App);
// clang-format on

class wxGLCanvasSubClass : public wxGLCanvas
{
public:
  wxGLCanvasSubClass(wxFrame* parent);
  ~wxGLCanvasSubClass();
  void Paintit(wxPaintEvent& event);

protected:
  DECLARE_EVENT_TABLE();

private:
  void Render();

  wxGLContext* gl_context;
};

// clang-format off
BEGIN_EVENT_TABLE(wxGLCanvasSubClass, wxGLCanvas)
    EVT_PAINT(wxGLCanvasSubClass::Paintit)
END_EVENT_TABLE()
// clang-format on

wxGLCanvasSubClass::wxGLCanvasSubClass(wxFrame* parent)
    : wxGLCanvas(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0,
                 "GLCanvas")
{
  int argc = 1;
  char* argv[1] = {wxString((wxTheApp->argv)[0]).char_str()};
  // while !IsShown() ?
  gl_context = new wxGLContext(this);
  int loaded = gladLoadGL();
  // const GLubyte* glV = glGetString(GL_VERSION);
  std::cout << "GLAD loaded: " << loaded << "\nVersion: " << GLVersion.major << std::endl;
}

wxGLCanvasSubClass::~wxGLCanvasSubClass()
{
  delete gl_context;
}

void wxGLCanvasSubClass::Paintit(wxPaintEvent& WXUNUSED(event)) { Render(); }

void wxGLCanvasSubClass::Render()
{
  SetCurrent();
  wxPaintDC(this);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  // glClear(GL_COLOR_BUFFER_BIT);  // TODO depth?
  // glViewport(0, 0, (GLint)GetSize().x, (GLint)GetSize().y);

  // glBegin(GL_POLYGON);
  // glColor3f(1.0, 1.0, 1.0);
  // glVertex2f(-0.5, -0.5);
  // glVertex2f(-0.5, 0.5);
  // glVertex2f(0.5, 0.5);
  // glVertex2f(0.5, -0.5);
  // glColor3f(0.4, 0.5, 0.4);
  // glVertex2f(0.0, -0.8);
  // glEnd();

  // glBegin(GL_POLYGON);
  // glColor3f(1.0, 0.0, 0.0);
  // glVertex2f(0.1, 0.1);
  // glVertex2f(-0.1, 0.1);
  // glVertex2f(-0.1, -0.1);
  // glVertex2f(0.1, -0.1);
  // glEnd();

  // glFlush();
  SwapBuffers();
}

bool App::OnInit()
{
  Frame* frame = new Frame("Hello World", wxPoint(50, 50), wxSize(450, 340));
  new wxGLCanvasSubClass(frame);
  frame->Show(true);
  return true;
}

Frame::Frame(const wxString& title, const wxPoint& pos, const wxSize& size)
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

void Frame::OnExit(wxCommandEvent& event) { Close(true); }

void Frame::OnAbout(wxCommandEvent& event)
{
  wxMessageBox("This is a wxWidgets' Hello world example", "About Hello World",
               wxOK | wxICON_INFORMATION);
}

void Frame::OnHello(wxCommandEvent& event)
{
  wxLogMessage("Hello World from wxWidgets!");
}
