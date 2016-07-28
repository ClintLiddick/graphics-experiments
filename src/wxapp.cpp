#include <memory>
#include <stdexcept>
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

class Canvas : public wxGLCanvas
{
public:
  Canvas(wxFrame* parent);
  void OnPaint(wxPaintEvent& event);

protected:
  DECLARE_EVENT_TABLE();

private:
  std::unique_ptr<wxGLContext> gl_context;
};

// clang-format off
BEGIN_EVENT_TABLE(Canvas, wxGLCanvas)
    EVT_PAINT(Canvas::OnPaint)
END_EVENT_TABLE()
// clang-format on

Canvas::Canvas(wxFrame* parent)
    : wxGLCanvas(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, 0,
                 "GLCanvas")
{
  int argc = 1;
  char* argv[1] = {wxString((wxTheApp->argv)[0]).char_str()};
  // while !IsShown() ?
  gl_context = std::make_unique<wxGLContext>(this);
  SetCurrent(*gl_context);

  if (gl3wInit()) {
    throw std::runtime_error("Failed to load OpenGL context");
  }
}

void Canvas::OnPaint(wxPaintEvent& WXUNUSED(event))
{
  wxPaintDC(this);
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT);  // TODO depth?


  glFlush();
  SwapBuffers();
}

bool App::OnInit()
{
  Frame* frame = new Frame("Hello World", wxPoint(50, 50), wxSize(450, 340));
  frame->Show(true);
  new Canvas(frame);
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
