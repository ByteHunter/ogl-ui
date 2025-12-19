#define _CRT_SECURE_NO_WARNINGS

#include "gui.h"

//-----------------------------------------------
// STATIC
//-----------------------------------------------
Static::Static(void) {
  // Position
  x = 0;
  y = 0;
  z = 0;
  // Size
  w = 50;
  h = 20;
  // Border, margin, padding
  b = 5;

  // Drawing control
  visible = true;
  state = 0;

  // Text
  text = NULL;

  // Mouse buttons information
  mleft = false;
  mmiddle = false;
  mright = false;
}

Static::Static(float xpos, float ypos, float zpos, float width, float height,
               bool vis, const char *txt) {
  // Position
  x = xpos;
  y = ypos;
  z = zpos;
  // Size
  w = width;
  h = height;
  // Border, margin, padding.
  b = 5;
  // Setup drawing control
  visible = vis;

  // Set text
  size_t len = sizeof(txt);
  text = new char[len];
  memcpy((void *)&text, (const void *)&txt, len);

  // Mouse buttons information
  mleft = false;
  mmiddle = false;
  mright = false;
}

//
// Set text of control
//
void Static::SetText(const char *txt) {
  unsigned int len = sizeof(txt);
  // delete[] text;
  text = new char[len];
  memcpy((void *)&text, (const void *)&txt, len);
}

void Static::SetFloat(float value) {
  // delete[] text;
  text = new char[32];
  sprintf(text, "%.4f", value);
}

void Static::SetFloat(const char *fmt, float value) {
  // delete[] text;
  text = new char[32];
  sprintf(text, fmt, value);
}

void Static::Render(void) {
  if (!visible)
    return;
  if (text == NULL)
    return;

  glPushMatrix();
  glColor3f(0.8f, 0.8f, 0.8f);
  glRasterPos3f(x, y + h - b, z + 1);
  glPushAttrib(GL_LIST_BIT);
  glListBase(font - 32);
  glCallLists((GLsizei)strlen(text), GL_UNSIGNED_BYTE, text);
  glPopAttrib();
  glPopMatrix();
}

//-----------------------------------------------
// BUTTON
//-----------------------------------------------
Button::Button(void) {
  x = 0;
  y = 0;
  z = 0;
  w = 50;
  h = 20;
  b = 5;

  visible = true;
  state = 0;
  text = NULL;

  mleft = false;
  mmiddle = false;
  mright = false;
}

Button::Button(float xpos, float ypos, float zpos, float width, float height,
               bool vis, const char *txt) {
  x = xpos;
  y = ypos;
  z = zpos;
  w = width;
  h = height;
  b = 5;
  visible = vis;
  state = 0;
  size_t len = sizeof(txt);
  text = new char[len];
  memcpy((void *)&text, (const void *)&txt, len);

  mleft = false;
  mmiddle = false;
  mright = false;
}

void Button::SetText(const char *txt) {
  size_t len = sizeof(txt);
  // delete[] text;
  text = new char[len];
  memcpy((void *)&text, (const void *)&txt, len);
}

void Button::Render(void) {
  if (!visible)
    return;

  glPushMatrix();
  // Render fill
  if (state == 0)
    glColor3f(0.05f, 0.05f, 0.05f);
  if (state == 1)
    glColor3f(0.15f, 0.15f, 0.15f);
  if (state == 2)
    glColor3f(0.05f, 0.05f, 0.05f);
  glBegin(GL_QUADS);
  glVertex3f(x, y + b, z);
  glVertex3f(x + b, y, z);
  glVertex3f(x + w, y, z);
  glVertex3f(x + w, y + h - b, z);
  glVertex3f(x + w, y + h - b, z);
  glVertex3f(x + w - b, y + h, z);
  glVertex3f(x, y + h, z);
  glVertex3f(x, y + b, z);
  glEnd();

  // Render border
  if (state == 0)
    glColor3f(0.6f, 0.6f, 0.6f);
  if (state == 1)
    glColor3f(0.4f, 0.4f, 0.4f);
  if (state == 2)
    glColor3f(0.8f, 0.8f, 0.8f);
  glBegin(GL_LINE_LOOP);
  glVertex3f(x, y + b, z + 0.01f);
  glVertex3f(x + b, y, z + 0.01f);
  glVertex3f(x + w, y, z + 0.01f);
  glVertex3f(x + w, y + h - b, z + 0.01f);
  glVertex3f(x + w - b, y + h, z + 0.01f);
  glVertex3f(x, y + h, z + 0.01f);
  glEnd();
  glPopMatrix();

  if (text == NULL)
    return;

  glPushMatrix();
  glColor3f(0.8f, 0.8f, 0.8f);
  glRasterPos3f(x + b + ((state == 1) ? 1 : 0),
                y + h - b + ((state == 1) ? 1 : 0), z + 1);
  glPushAttrib(GL_LIST_BIT);
  glListBase(font - 32);
  glCallLists((GLsizei)strlen(text), GL_UNSIGNED_BYTE, text);
  glPopAttrib();
  glPopMatrix();
}

int Button::LDown(float xpos, float ypos) {
  if (!visible)
    return 0;
  if (!((xpos >= x) && (xpos <= (x + w)) && (ypos >= y) && (ypos <= (y + h)))) {
    return 0;
  } else {
    SetCursor(LoadCursor(NULL, IDC_HAND));
    state = 1;
    mleft = true;
    return 1;
  }
}

int Button::LUp(float xpos, float ypos) {
  if (!visible)
    return 0;
  state = 0;
  if (!((xpos >= x) && (xpos <= (x + w)) && (ypos >= y) && (ypos <= (y + h)))) {
    mleft = false;
    return 0;
  } else {
    if (mleft) {
      mleft = false;
      return 1;
    }
  }
  return 0;
}

int Button::Over(float xpos, float ypos, bool lmb) {
  if (!visible)
    return 0;
  if (lmb)
    return 0;
  if (!((xpos >= x) && (xpos <= (x + w)) && (ypos >= y) && (ypos <= (y + h)))) {
    if (!mleft)
      state = 0;
    return 0;
  } else {
    SetCursor(LoadCursor(NULL, IDC_HAND));
    if (mleft)
      state = 1;
    else
      state = 2;
    return 1;
  }
}

//-----------------------------------------------
// FRAME
//-----------------------------------------------
Frame::Frame(void) {
  x = 0;
  y = 0;
  z = 0;
  w = 50;
  h = 40;
  hw = w;
  hh = 20;
  b = 5;

  visible = true;
  movable = false;
  state = 0;
  text = NULL;

  mleft = false;
  mmiddle = false;
  mright = false;
}

Frame::Frame(float xpos, float ypos, float zpos, float width, float height,
             bool vis, const char *txt) {
  x = xpos;
  y = ypos;
  z = zpos;
  w = width;
  h = height;
  hw = width;
  hh = 20;
  visible = vis;
  movable = false;
  size_t len = sizeof(txt);
  text = new char[len];
  memcpy((void *)&text, (const void *)&txt, len);

  mleft = false;
  mmiddle = false;
  mright = false;
}

void Frame::SetText(const char *txt) {
  unsigned int len = sizeof(txt);
  // delete[] text;
  text = new char[len];
  memcpy((void *)&text, (const void *)&txt, len);
  // text = (char*)txt;
}

void Frame::AddControl(void *_pcontrol) { child_controls.push_back(_pcontrol); }

void Frame::Show(bool _b) {
  visible = _b;
  for (unsigned int i = 0; i < child_controls.size(); i++) {
    ((Control *)child_controls[i])->visible = _b;
  }
}

void Frame::Render(void) {
  if (!visible)
    return;

  glPushMatrix();
  // Render header fill
  glColor3f(0.15f, 0.15f, 0.15f);
  glBegin(GL_POLYGON);
  glVertex3f(x, y + 5, z);
  glVertex3f(x + 5, y, z);
  glVertex3f(x + w, y, z);
  glVertex3f(x + w, y + hh, z);
  glVertex3f(x, y + hh, z);
  glEnd();
  glColor3f(0.05f, 0.05f, 0.05f);
  glBegin(GL_POLYGON);
  glVertex3f(x, y + hh, z);
  glVertex3f(x + w, y + hh, z);
  glVertex3f(x + w, y + h - 5, z);
  glVertex3f(x + w - 5, y + h, z);
  glVertex3f(x, y + h, z);
  glEnd();

  // Render border
  if (state == 0)
    glColor3f(0.6f, 0.6f, 0.6f);
  if (state == 1)
    glColor3f(0.4f, 0.4f, 0.4f);
  if (state == 2)
    glColor3f(0.8f, 0.8f, 0.8f);
  glBegin(GL_LINE_LOOP);
  glVertex3f(x, y + 5, z + 0.01f);
  glVertex3f(x + 5, y, z + 0.01f);
  glVertex3f(x + w, y, z + 0.01f);
  glVertex3f(x + w, y + h - 5, z + 0.01f);
  glVertex3f(x + w - 5, y + h, z + 0.01f);
  glVertex3f(x, y + h, z + 0.01f);
  glEnd();
  glBegin(GL_LINES);
  glVertex3f(x + w, y + hh, z + 0.01f);
  glVertex3f(x, y + hh, z + 0.01f);
  glEnd();
  glPopMatrix();

  if (text == NULL)
    return;

  glPushMatrix();
  glColor3f(0.8f, 0.8f, 0.8f);
  glRasterPos3f(x + 5, y + hh - 5, z + 1);
  glPushAttrib(GL_LIST_BIT);
  glListBase(font - 32);
  glCallLists((GLsizei)strlen(text), GL_UNSIGNED_BYTE, text);
  glPopAttrib();
  glPopMatrix();
}

int Frame::LDown(float xpos, float ypos) {
  if (!visible)
    return 0;
  if (!((xpos >= x) && (xpos <= (x + w)) && (ypos >= y) &&
        (ypos <= (y + hh)))) {
    return 0;
  } else {
    mleft = true;
    if (movable) {
      xi = xpos;
      yi = ypos;
      z += 5;
      for (unsigned int i = 0; i < child_controls.size(); i++)
        ((Control *)child_controls[i])->z += 5;
    }
    return 1;
  }
}

int Frame::LUp(float xpos, float ypos) {
  if (!visible)
    return 0;
  state = 0;
  if (!((xpos >= x) && (xpos <= (x + w)) && (ypos >= y) &&
        (ypos <= (y + hh)))) {
    mleft = false;
    return 0;
  } else {
    if (mleft) {
      mleft = false;
      if (movable) {
        z -= 5;
        for (unsigned int i = 0; i < child_controls.size(); i++)
          ((Control *)child_controls[i])->z -= 5;
      }
      return 1;
    }
  }
  return 0;
}

int Frame::Over(float xpos, float ypos, bool lmb) {
  if (!visible)
    return 0;
  if (lmb && !mleft)
    return 0;
  if (!((xpos >= x) && (xpos <= (x + w)) && (ypos >= y) &&
        (ypos <= (y + hh)))) {
    return 0;
  } else {
    if (mleft && movable) {
      xf = xpos;
      yf = ypos;
      xd = xf - xi;
      yd = yf - yi;
      x += xd;
      y += yd;
      xi = xpos;
      yi = ypos;
      state = 1;
      for (unsigned int i = 0; i < child_controls.size(); i++) {
        ((Control *)child_controls[i])->x += xd;
        ((Control *)child_controls[i])->y += yd;
      }
    }
    return 1;
  }
}

//-----------------------------------------------
// EDIT
//-----------------------------------------------
Edit::Edit(void) {
  x = 0;
  y = 0;
  z = 0;
  w = 50;
  h = 40;
  b = 5;

  visible = true;
  state = 0;
  text = NULL;

  mleft = false;
  mmiddle = false;
  mright = false;
}

Edit::Edit(float xpos, float ypos, float zpos, float width, float height,
           bool vis, const char *txt) {
  x = xpos;
  y = ypos;
  z = zpos;
  w = width;
  h = height;
  b = 5;
  visible = vis;
  state = 0;
  size_t len = sizeof(txt);
  text = new char[len];
  memcpy((void *)&text, (const void *)&txt, len);

  mleft = false;
  mmiddle = false;
  mright = false;
}

void Edit::SetText(const char *txt) {
  unsigned int len = sizeof(txt);
  // delete[] text;
  text = new char[len];
  memcpy((void *)&text, (const void *)&txt, len);
  // text = (char*)txt;
}

void Edit::Render(void) {
  if (!visible)
    return;

  glPushMatrix();
  // Render fill
  glColor3f(0.05f, 0.05f, 0.05f);
  glBegin(GL_QUADS);
  glVertex3f(x, y, z);
  glVertex3f(x + w, y, z);
  glVertex3f(x + w, y + h, z);
  glVertex3f(x, y + h, z);
  glEnd();

  // Render border
  if (state == 0)
    glColor3f(0.6f, 0.6f, 0.6f);
  if (state == 1)
    glColor3f(0.4f, 0.4f, 0.4f);
  glBegin(GL_LINE_LOOP);
  glVertex3f(x, y, z + 0.01f);
  glVertex3f(x + w, y, z + 0.01f);
  glVertex3f(x + w, y + h, z + 0.01f);
  glVertex3f(x, y + h, z + 0.01f);
  glEnd();
  glPopMatrix();

  if (text == NULL)
    return;

  glPushMatrix();
  glColor3f(0.8f, 0.8f, 0.8f);
  glRasterPos3f(x + b, y + h - b, z + 0.02f);
  glPushAttrib(GL_LIST_BIT);
  glListBase(font - 32);
  glCallLists((GLsizei)strlen(text), GL_UNSIGNED_BYTE, text);
  glPopAttrib();
  glPopMatrix();
}

int Edit::LDown(float xpos, float ypos) {
  if (!visible)
    return 0;
  if (!((xpos >= x) && (xpos <= (x + w)) && (ypos >= y) && (ypos <= (y + h)))) {
    state = 0;
    return 0;
  } else {
    state = 1;
    return 1;
  }
}

//-----------------------------------------------
// CHECKBOX
//-----------------------------------------------
CheckBox::CheckBox(void) {
  x = 0;
  y = 0;
  z = 0;
  w = 50;
  h = 40;
  b = 5;

  visible = true;
  state = 0;
  text = NULL;

  mleft = false;
  mmiddle = false;
  mright = false;
}

CheckBox::CheckBox(float xpos, float ypos, float zpos, float width,
                   float height, bool vis, const char *txt) {
  x = xpos;
  y = ypos;
  z = zpos;
  w = width;
  h = height;
  visible = vis;
  state = 0;
  size_t len = sizeof(txt);
  // delete[] text;
  text = new char[len];
  memcpy((void *)&text, (const void *)&txt, len);

  mleft = false;
  mmiddle = false;
  mright = false;
}

void CheckBox::Render(void) {
  if (!visible)
    return;

  glPushMatrix();
  // Render fill
  glColor3f(0.05f, 0.05f, 0.05f);
  glBegin(GL_POLYGON);
  glVertex3f(x, y, z);
  glVertex3f(x + w, y, z);
  glVertex3f(x + w, y + h - b, z);
  glVertex3f(x + w - b, y + h, z);
  glVertex3f(x, y + h, z);
  glEnd();

  if (state == 1) {
    x += 4;
    y += 4;
    h -= 8;
    w -= 8;
    glColor3f(0.25f, 0.25f, 0.25f);
    glBegin(GL_POLYGON);
    glVertex3f(x, y, z + 0.01f);
    glVertex3f(x + w, y, z + 0.01f);
    glVertex3f(x + w, y + h - b, z + 0.01f);
    glVertex3f(x + w - b, y + h, z + 0.01f);
    glVertex3f(x, y + h, z + 0.01f);
    glEnd();
    x -= 4;
    y -= 4;
    h += 8;
    w += 8;
  }

  // Render border
  glColor3f(0.6f, 0.6f, 0.6f);
  glBegin(GL_LINE_LOOP);
  glVertex3f(x, y, z + 0.02f);
  glVertex3f(x + w, y, z + 0.02f);
  glVertex3f(x + w, y + h - b, z + 0.02f);
  glVertex3f(x + w - b, y + h, z + 0.02f);
  glVertex3f(x, y + h, z + 0.02f);
  glEnd();

  glColor3f(0.4f, 0.4f, 0.4f);
  x += 4;
  y += 4;
  h -= 8;
  w -= 8;
  glBegin(GL_LINE_LOOP);
  glVertex3f(x, y, z + 0.02f);
  glVertex3f(x + w, y, z + 0.02f);
  glVertex3f(x + w, y + h - b, z + 0.02f);
  glVertex3f(x + w - b, y + h, z + 0.02f);
  glVertex3f(x, y + h, z + 0.02f);
  glEnd();
  x -= 4;
  y -= 4;
  h += 8;
  w += 8;
  glPopMatrix();
}

int CheckBox::LDown(float xpos, float ypos) {
  if (!visible)
    return 0;
  if (!((xpos >= x) && (xpos <= (x + w)) && (ypos >= y) && (ypos <= (y + h)))) {
    return 0;
  } else {
    mleft = true;
    return 1;
  }
}

int CheckBox::LUp(float xpos, float ypos) {
  if (!visible)
    return 0;
  if (!((xpos >= x) && (xpos <= (x + w)) && (ypos >= y) && (ypos <= (y + h)))) {
    mleft = false;
    return 0;
  } else {
    if (mleft) {
      mleft = false;
      if (state != 1)
        state = 1;
      else
        state = 0;
      return 1;
    }
  }
  return 0;
}

int CheckBox::Over(float xpos, float ypos, bool lmb) {
  // TODO: make it glow when hovering over
  return 0;
}

//-----------------------------------------------
// EditNumber
//-----------------------------------------------
EditNumber::EditNumber(void) {
  x = 0;
  y = 0;
  z = 0;
  w = 50;
  h = 40;
  b = 5;

  visible = true;
  state = 0;
  lstate = 0;
  rstate = 0;
  value = 0;
  min = 1;
  max = 10;
  step = 1;

  mleft = false;
  mmiddle = false;
  mright = false;
}

EditNumber::EditNumber(float xpos, float ypos, float zpos, float width,
                       float height, bool vis, int val) {
  x = xpos;
  y = ypos;
  z = zpos;
  w = width;
  h = height;
  b = 5;
  visible = vis;
  state = 0;
  lstate = 0;
  rstate = 0;
  value = val;
  min = 1;
  max = 10;
  step = 1;

  mleft = false;
  mmiddle = false;
  mright = false;

  sprintf(rtext, "%d", val);
}

void EditNumber::Render(void) {
  if (!visible)
    return;

  // Fill
  glPushMatrix();
  // Middle
  if (state == 0)
    glColor3f(0.05f, 0.05f, 0.05f);
  if (state == 1)
    glColor3f(0.15f, 0.15f, 0.15f);
  if (state == 2)
    glColor3f(0.05f, 0.05f, 0.05f);
  glBegin(GL_POLYGON);
  glEnd();
  // Left
  if (lstate == 0)
    glColor3f(0.05f, 0.05f, 0.05f);
  if (lstate == 1)
    glColor3f(0.15f, 0.15f, 0.15f);
  if (lstate == 2)
    glColor3f(0.05f, 0.05f, 0.05f);
  glBegin(GL_POLYGON);
  glVertex3f(x, y + b, z);
  glVertex3f(x + b, y, z);
  glVertex3f(x + 20, y, z);
  glVertex3f(x + 20, y + h, z);
  glVertex3f(x, y + h, z);
  glEnd();
  // Right
  if (rstate == 0)
    glColor3f(0.05f, 0.05f, 0.05f);
  if (rstate == 1)
    glColor3f(0.15f, 0.15f, 0.15f);
  if (rstate == 2)
    glColor3f(0.05f, 0.05f, 0.05f);
  glBegin(GL_POLYGON);
  glVertex3f(x + w - 20, y, z);
  glVertex3f(x + w, y, z);
  glVertex3f(x + w, y + h - 5, z);
  glVertex3f(x + w - 5, y + h, z);
  glVertex3f(x + w - 20, y + h, z);
  glEnd();

  // Borders
  // middle
  if (state == 0)
    glColor3f(0.6f, 0.6f, 0.6f);
  if (state == 1)
    glColor3f(0.4f, 0.4f, 0.4f);
  if (state == 2)
    glColor3f(0.8f, 0.8f, 0.8f);
  glBegin(GL_LINES);
  glVertex3f(x + 20, y, z + 0.01f);
  glVertex3f(x + w - 20, y, z + 0.01f);
  glVertex3f(x + 20, y + h, z + 0.01f);
  glVertex3f(x + w - 20, y + h, z + 0.01f);
  glEnd();
  // left
  if (lstate == 0)
    glColor3f(0.6f, 0.6f, 0.6f);
  if (lstate == 1)
    glColor3f(0.4f, 0.4f, 0.4f);
  if (lstate == 2)
    glColor3f(0.8f, 0.8f, 0.8f);
  glBegin(GL_LINE_LOOP);
  glVertex3f(x, y + b, z + 0.01f);
  glVertex3f(x + b, y, z + 0.01f);
  glVertex3f(x + 20, y, z + 0.01f);
  glVertex3f(x + 20, y + h, z + 0.01f);
  glVertex3f(x, y + h, z + 0.01f);
  glEnd();
  // right
  if (rstate == 0)
    glColor3f(0.6f, 0.6f, 0.6f);
  if (rstate == 1)
    glColor3f(0.4f, 0.4f, 0.4f);
  if (rstate == 2)
    glColor3f(0.8f, 0.8f, 0.8f);
  glBegin(GL_LINE_LOOP);
  glVertex3f(x + w - 20, y, z + 0.01f);
  glVertex3f(x + w, y, z + 0.01f);
  glVertex3f(x + w, y + h - 5, z + 0.01f);
  glVertex3f(x + w - 5, y + h, z + 0.01f);
  glVertex3f(x + w - 20, y + h, z + 0.01f);
  glEnd();

  // Symbols
  glBegin(GL_LINES);
  // minus
  if (lstate == 0)
    glColor3f(0.6f, 0.6f, 0.6f);
  if (lstate == 1)
    glColor3f(0.4f, 0.4f, 0.4f);
  if (lstate == 2)
    glColor3f(0.8f, 0.8f, 0.8f);
  glVertex3f(x + 5 + ((lstate == 1) ? 1 : 0),
             y + h / 2 + ((lstate == 1) ? 1 : 0), z + 0.01f);
  glVertex3f(x + 15 + ((lstate == 1) ? 1 : 0),
             y + h / 2 + ((lstate == 1) ? 1 : 0), z + 0.01f);
  // plus
  if (rstate == 0)
    glColor3f(0.6f, 0.6f, 0.6f);
  if (rstate == 1)
    glColor3f(0.4f, 0.4f, 0.4f);
  if (rstate == 2)
    glColor3f(0.8f, 0.8f, 0.8f);
  glVertex3f(x + w - 15 + ((rstate == 1) ? 1 : 0),
             y + h / 2 + ((rstate == 1) ? 1 : 0), z + 0.01f);
  glVertex3f(x + w - 5 + ((rstate == 1) ? 1 : 0),
             y + h / 2 + ((rstate == 1) ? 1 : 0), z + 0.01f);
  glVertex3f(x + w - 10 + ((rstate == 1) ? 1 : 0),
             y + 5 + ((rstate == 1) ? 1 : 0), z + 0.01f);
  glVertex3f(x + w - 10 + ((rstate == 1) ? 1 : 0),
             y + 15 + ((rstate == 1) ? 1 : 0), z + 0.01f);
  glEnd();

  glPopMatrix();

  glPushMatrix();
  glColor3f(0.8f, 0.8f, 0.8f);
  glRasterPos3f(x + b + 20, y + h - b, z + 1);
  glPushAttrib(GL_LIST_BIT);
  glListBase(font - 32);
  glCallLists((GLsizei)strlen(rtext), GL_UNSIGNED_BYTE, rtext);
  glPopAttrib();
  glPopMatrix();
}

int EditNumber::LDown(float xpos, float ypos) {
  if (!visible)
    return 0;
  // check left
  if (((xpos >= x) && (xpos <= (x + 20)) && (ypos >= y) && (ypos <= (y + h))))
  {
    SetCursor(LoadCursor(NULL, IDC_HAND));
    lstate = 1;
    mleft = true;
    value = (value > min) ? value - step : min;
    if (value < min)
      value = min;
    sprintf(rtext, "%d", value);
    return 1;
  }
  // check right
  if (((xpos >= (x + w - 20)) && (xpos <= (x + w)) && (ypos >= y) &&
       (ypos <= (y + h))))
  {
    SetCursor(LoadCursor(NULL, IDC_HAND));
    rstate = 1;
    mleft = true;
    value = (value < max) ? value + step : max;
    if (value > max)
      value = max;
    sprintf(rtext, "%d", value);
    return 1;
  }
  return 1;
}

int EditNumber::LUp(float xpos, float ypos) {
  if (!visible)
    return 0;
  lstate = 0;
  rstate = 0;
  // check left
  if (!((xpos >= x) && (xpos <= (x + 20)) && (ypos >= y) &&
        (ypos <= (y + h)))) {
    mleft = false;
  } else {
    if (mleft) {
      mleft = false;
    }
  }
  // check right
  if (!((xpos >= (x + w - 20)) && (xpos <= (x + w)) && (ypos >= y) &&
        (ypos <= (y + h)))) {
    mleft = false;
  } else {
    if (mleft) {
      mleft = false;
    }
  }
  if (!((xpos >= x) && (xpos <= (x + 20)) && (ypos >= y) &&
        (ypos <= (y + h))) &&
      !((xpos >= (x + w - 20)) && (xpos <= (x + w)) && (ypos >= y) &&
        (ypos <= (y + h))))
    return 0;
  else
    return 1;
}

int EditNumber::Over(float xpos, float ypos, bool lmb) {
  if (!visible)

    return 0;
  if (lmb)
    return 0;
  // check left
  if (!((xpos >= x) && (xpos <= (x + 20)) && (ypos >= y) &&
        (ypos <= (y + h)))) {
    if (!mleft)
      lstate = 0;
  } else {
    SetCursor(LoadCursor(NULL, IDC_HAND));
    if (mleft)
      lstate = 1;
    else
      lstate = 2;
  }
  // check right
  if (!((xpos >= (x + w - 20)) && (xpos <= (x + w)) && (ypos >= y) &&
        (ypos <= (y + h)))) {
    if (!mleft)
      rstate = 0;
  } else {
    SetCursor(LoadCursor(NULL, IDC_HAND));
    if (mleft)
      rstate = 1;
    else
      rstate = 2;
  }
  if (!((xpos >= x) && (xpos <= (x + w)) && (ypos >= y) && (ypos <= (y + h))))
    return 0;
  else
    return 1;
}

//-----------------------------------------------
// EditNumberF
//-----------------------------------------------
EditNumberF::EditNumberF(void) {
  x = 0;
  y = 0;
  z = 0;
  w = 50;
  h = 40;
  b = 5;

  visible = true;
  state = 0;
  lstate = 0;
  rstate = 0;
  value = 0;
  min = 1;
  max = 10;
  step = 1;

  mleft = false;
  mmiddle = false;
  mright = false;
}

EditNumberF::EditNumberF(float xpos, float ypos, float zpos, float width,
                         float height, bool vis, float val, float _min,
                         float _max, float _step) {
  x = xpos;
  y = ypos;
  z = zpos;
  w = width;
  h = height;
  b = 5;
  visible = vis;
  state = 0;
  lstate = 0;
  rstate = 0;
  value = val;
  min = _min;
  max = _max;
  step = _step;

  mleft = false;
  mmiddle = false;
  mright = false;

  sprintf(rtext, "%.2f", val);
}

void EditNumberF::Render(void) {
  if (!visible)
    return;

  // Fill
  glPushMatrix();
  // Middle
  if (state == 0)
    glColor3f(0.05f, 0.05f, 0.05f);
  if (state == 1)
    glColor3f(0.15f, 0.15f, 0.15f);
  if (state == 2)
    glColor3f(0.05f, 0.05f, 0.05f);
  glBegin(GL_POLYGON);
  glEnd();
  // Left
  if (lstate == 0)
    glColor3f(0.05f, 0.05f, 0.05f);
  if (lstate == 1)
    glColor3f(0.15f, 0.15f, 0.15f);
  if (lstate == 2)
    glColor3f(0.05f, 0.05f, 0.05f);
  glBegin(GL_POLYGON);
  glVertex3f(x, y + b, z);
  glVertex3f(x + b, y, z);
  glVertex3f(x + 20, y, z);
  glVertex3f(x + 20, y + h, z);
  glVertex3f(x, y + h, z);
  glEnd();
  // Right
  if (rstate == 0)
    glColor3f(0.05f, 0.05f, 0.05f);
  if (rstate == 1)
    glColor3f(0.15f, 0.15f, 0.15f);
  if (rstate == 2)
    glColor3f(0.05f, 0.05f, 0.05f);
  glBegin(GL_POLYGON);
  glVertex3f(x + w - 20, y, z);
  glVertex3f(x + w, y, z);
  glVertex3f(x + w, y + h - 5, z);
  glVertex3f(x + w - 5, y + h, z);
  glVertex3f(x + w - 20, y + h, z);
  glEnd();

  // Borders
  // middle
  if (state == 0)
    glColor3f(0.6f, 0.6f, 0.6f);
  if (state == 1)
    glColor3f(0.4f, 0.4f, 0.4f);
  if (state == 2)
    glColor3f(0.8f, 0.8f, 0.8f);
  glBegin(GL_LINES);
  glVertex3f(x + 20, y, z + 0.01f);
  glVertex3f(x + w - 20, y, z + 0.01f);
  glVertex3f(x + 20, y + h, z + 0.01f);
  glVertex3f(x + w - 20, y + h, z + 0.01f);
  glEnd();
  // left
  if (lstate == 0)
    glColor3f(0.6f, 0.6f, 0.6f);
  if (lstate == 1)
    glColor3f(0.4f, 0.4f, 0.4f);
  if (lstate == 2)
    glColor3f(0.8f, 0.8f, 0.8f);
  glBegin(GL_LINE_LOOP);
  glVertex3f(x, y + b, z + 0.01f);
  glVertex3f(x + b, y, z + 0.01f);
  glVertex3f(x + 20, y, z + 0.01f);
  glVertex3f(x + 20, y + h, z + 0.01f);
  glVertex3f(x, y + h, z + 0.01f);
  glEnd();
  // right
  if (rstate == 0)
    glColor3f(0.6f, 0.6f, 0.6f);
  if (rstate == 1)
    glColor3f(0.4f, 0.4f, 0.4f);
  if (rstate == 2)
    glColor3f(0.8f, 0.8f, 0.8f);
  glBegin(GL_LINE_LOOP);
  glVertex3f(x + w - 20, y, z + 0.01f);
  glVertex3f(x + w, y, z + 0.01f);
  glVertex3f(x + w, y + h - 5, z + 0.01f);
  glVertex3f(x + w - 5, y + h, z + 0.01f);
  glVertex3f(x + w - 20, y + h, z + 0.01f);
  glEnd();

  // Symbols
  glBegin(GL_LINES);
  // minus
  if (lstate == 0)
    glColor3f(0.6f, 0.6f, 0.6f);
  if (lstate == 1)
    glColor3f(0.4f, 0.4f, 0.4f);
  if (lstate == 2)
    glColor3f(0.8f, 0.8f, 0.8f);
  glVertex3f(x + 5 + ((lstate == 1) ? 1 : 0),
             y + h / 2 + ((lstate == 1) ? 1 : 0), z + 0.01f);
  glVertex3f(x + 15 + ((lstate == 1) ? 1 : 0),
             y + h / 2 + ((lstate == 1) ? 1 : 0), z + 0.01f);
  // plus
  if (rstate == 0)
    glColor3f(0.6f, 0.6f, 0.6f);
  if (rstate == 1)
    glColor3f(0.4f, 0.4f, 0.4f);
  if (rstate == 2)
    glColor3f(0.8f, 0.8f, 0.8f);
  glVertex3f(x + w - 15 + ((rstate == 1) ? 1 : 0),
             y + h / 2 + ((rstate == 1) ? 1 : 0), z + 0.01f);
  glVertex3f(x + w - 5 + ((rstate == 1) ? 1 : 0),
             y + h / 2 + ((rstate == 1) ? 1 : 0), z + 0.01f);
  glVertex3f(x + w - 10 + ((rstate == 1) ? 1 : 0),
             y + 5 + ((rstate == 1) ? 1 : 0), z + 0.01f);
  glVertex3f(x + w - 10 + ((rstate == 1) ? 1 : 0),
             y + 15 + ((rstate == 1) ? 1 : 0), z + 0.01f);
  glEnd();

  glPopMatrix();

  glPushMatrix();
  glColor3f(0.8f, 0.8f, 0.8f);
  glRasterPos3f(x + b + 20, y + h - b, z + 1);
  glPushAttrib(GL_LIST_BIT);
  glListBase(font - 32);
  glCallLists((GLsizei)strlen(rtext), GL_UNSIGNED_BYTE, rtext);
  glPopAttrib();
  glPopMatrix();
}

int EditNumberF::LDown(float xpos, float ypos) {
  if (!visible)
    return 0;
  // check left
  if (((xpos >= x) && (xpos <= (x + 20)) && (ypos >= y) && (ypos <= (y + h))))
  {
    SetCursor(LoadCursor(NULL, IDC_HAND));
    lstate = 1;
    mleft = true;
    value = (value > min) ? value - step : value;
    sprintf(rtext, "%.2f", value);
    return 1;
  }
  // check right
  if (((xpos >= (x + w - 20)) && (xpos <= (x + w)) && (ypos >= y) &&
       (ypos <= (y + h))))
  {
    SetCursor(LoadCursor(NULL, IDC_HAND));
    rstate = 1;
    mleft = true;
    value = (value < max) ? value + step : max;
    sprintf(rtext, "%.2f", value);
    return 1;
  }
  return 1;
}

int EditNumberF::LUp(float xpos, float ypos) {
  if (!visible)
    return 0;
  lstate = 0;
  rstate = 0;
  // check left
  if (!((xpos >= x) && (xpos <= (x + 20)) && (ypos >= y) &&
        (ypos <= (y + h)))) {
    mleft = false;
  } else {
    if (mleft) {
      mleft = false;
    }
  }
  // check right
  if (!((xpos >= (x + w - 20)) && (xpos <= (x + w)) && (ypos >= y) &&
        (ypos <= (y + h)))) {
    mleft = false;
  } else {
    if (mleft) {
      mleft = false;
    }
  }
  if (!((xpos >= x) && (xpos <= (x + 20)) && (ypos >= y) &&
        (ypos <= (y + h))) &&
      !((xpos >= (x + w - 20)) && (xpos <= (x + w)) && (ypos >= y) &&
        (ypos <= (y + h))))
    return 0;
  else
    return 1;
}

int EditNumberF::Over(float xpos, float ypos, bool lmb) {
  if (!visible)

    return 0;
  if (lmb)
    return 0;
  // check left
  if (!((xpos >= x) && (xpos <= (x + 20)) && (ypos >= y) &&
        (ypos <= (y + h)))) {
    if (!mleft)
      lstate = 0;
  } else {
    SetCursor(LoadCursor(NULL, IDC_HAND));
    if (mleft)
      lstate = 1;
    else
      lstate = 2;
  }
  // check right
  if (!((xpos >= (x + w - 20)) && (xpos <= (x + w)) && (ypos >= y) &&
        (ypos <= (y + h)))) {
    if (!mleft)
      rstate = 0;
  } else {
    SetCursor(LoadCursor(NULL, IDC_HAND));
    if (mleft)
      rstate = 1;
    else
      rstate = 2;
  }
  if (!((xpos >= x) && (xpos <= (x + w)) && (ypos >= y) && (ypos <= (y + h))))
    return 0;
  else
    return 1;
}

//-----------------------------------------------
// Slider
//-----------------------------------------------
Slider::Slider(void) {
  x = 0;
  y = 0;
  z = 0;
  w = 50;
  h = 20;
  b = 5;

  // Values
  value = 0;
  minv = 1;
  maxv = 10;
  step = 1;
  // Sizes
  pw = w / ((maxv - minv) / step);
  ph = h;
  px = x + pw * (value - 1);
  py = y;
  pz = z;

  visible = true;
  state = 0;
  text = NULL;

  mleft = false;
  mmiddle = false;
  mright = false;
}

Slider::Slider(float xpos, float ypos, float zpos, float width, float height,
               bool vis, int _val, int _min, int _max, int _step) {
  x = xpos;
  y = ypos;
  z = zpos;
  w = width;
  h = height;
  b = 3;
  visible = vis;
  state = 0;

  // Set boundaries
  value = _val;
  minv = _min;
  maxv = _max;
  step = _step;

  // Calculating sizes
  float pos = (((float)value - (float)minv) / (float)step);
  pw = (float)(w / (((float)maxv - (float)minv) / (float)step));
  if (pw < 10.0f)
    pw = 10.0f;
  vw = (w - pw) / (((float)maxv - (float)minv) / (float)step);
  ph = (float)h;
  px = (float)(x + vw * pos);
  py = (float)(ypos);
  pz = (float)(zpos + 0.01f);

  mleft = false;
  mmiddle = false;
  mright = false;
}

void Slider::Render(void) {
  if (!visible)
    return;
  glPushMatrix();

  // Draw lines
  glBegin(GL_LINE_LOOP);
  glColor3f(0.4f, 0.4f, 0.4f);
  glVertex3f(x, y + h / 2 - 2, z);
  glVertex3f(x + w, y + h / 2 - 2, z);
  glVertex3f(x + w, y + h / 2 + 1, z);
  glVertex3f(x, y + h / 2 + 1, z);
  glEnd();

  // Draw button
  if (state == 0)
    glColor3f(0.05f, 0.05f, 0.05f);
  if (state == 1)
    glColor3f(0.2f, 0.2f, 0.2f);
  if (state == 2)
    glColor3f(0.1f, 0.1f, 0.1f);
  glBegin(GL_POLYGON);
  glVertex3f(px, y, z + 0.01f);
  glVertex3f(px + pw, y, z + 0.01f);
  glVertex3f(px + pw, y + h, z + 0.01f);
  glVertex3f(px, y + h, z + 0.01f);
  glEnd();
  if (state == 0)
    glColor3f(0.5f, 0.5f, 0.5f);
  if (state == 1)
    glColor3f(0.4f, 0.4f, 0.4f);
  if (state == 2)
    glColor3f(0.8f, 0.8f, 0.8f);
  glBegin(GL_LINE_LOOP);
  glVertex3f(px, y, z + 0.02f);
  glVertex3f(px + pw, y, z + 0.02f);
  glVertex3f(px + pw, y + h, z + 0.02f);
  glVertex3f(px, y + h, z + 0.02f);
  glEnd();
  if (state == 0)
    glColor3f(0.5f, 0.5f, 0.5f);
  if (state == 1)
    glColor3f(0.4f, 0.4f, 0.4f);
  if (state == 2)
    glColor3f(0.8f, 0.8f, 0.8f);
  glBegin(GL_LINES);
  glVertex3f(px + 4, y + h / 2, z + 0.02f);
  glVertex3f(px + pw - 4, y + h / 2, z + 0.02f);
  glVertex3f(px + 4, y + h / 2 - 3, z + 0.02f);
  glVertex3f(px + pw - 4, y + h / 2 - 3, z + 0.02f);
  glVertex3f(px + 4, y + h / 2 + 3, z + 0.02f);
  glVertex3f(px + pw - 4, y + h / 2 + 3, z + 0.02f);
  glEnd();

  // Draw slider
  glPopMatrix();
}

int Slider::LDown(float xpos, float ypos) {
  if (!visible)
    return 0;
  float pos = (((float)value - (float)minv) / (float)step);
  if ((xpos >= px) && (xpos <= (px + pw)) && (ypos >= y) && (ypos <= (y + h))) {
    mleft = true;
    state = 1;
    x0 = xpos;
    SetCursor(LoadCursor(NULL, IDC_HAND));
  }
  return 0;
}

int Slider::LUp(float xpos, float ypos) {
  if (!visible)
    return 0;
  int res = 0;
  float pos = (((float)value - (float)minv) / (float)step);
  if ((xpos >= px) && (xpos <= (px + pw)) && (ypos >= y) && (ypos <= (y + h))) {
    state = 2;
  } else {
    state = 0;
  }
  if (mleft) {
    float dx = xpos - x0;
    px += dx;
    x0 = xpos;
    if (px < x)
      px = x;
    if (px > (x + w - pw))
      px = x + w - pw;
    int v = (int)((px - x) / vw);
    if (((px - x) - (v * vw)) < (vw / 2)) {
      px = x + vw * v;
    } else {
      px = x + vw * (v + 1);
    }
    res = 1;
  }
  mleft = false;
  return res;
}

int Slider::Over(float xpos, float ypos, bool lmb) {
  if (!visible)
    return 0;
  if (!mleft && lmb)
    return 0;
  float pos = (((float)value - (float)minv) / (float)step);
  if ((xpos >= px) && (xpos <= (px + pw)) && (ypos >= y) && (ypos <= (y + h))) {
    if (mleft)
      state = 1;
    else
      state = 2;
    SetCursor(LoadCursor(NULL, IDC_HAND));
  } else {
    if (mleft)
      state = 1;
    else
      state = 0;
  }
  if (mleft) {
    float dx = xpos - x0;
    px += dx;
    x0 = xpos;
    if (px < x)
      px = x;
    if (px > (x + w - pw))
      px = x + w - pw;
  }
  return 0;
}

//-----------------------------------------------
// Wheel
//-----------------------------------------------
Wheel::Wheel(void) {
  x = 0;
  y = 0;
  z = 0;
  w = 50;
  h = 20;
  b = 5;

  // Values
  value = 0;
  minv = 1;
  maxv = 10;
  step = 1;
  delta = 0;

  // Draw control
  visible = true;
  state = 0;
  text = NULL;

  mleft = false;
  mmiddle = false;
  mright = false;
}

Wheel::Wheel(float xpos, float ypos, float zpos, float width, float height,
             bool vis, float _val, float _min, float _max, float _step) {
  x = xpos;
  y = ypos;
  z = zpos;
  w = width;
  h = height;
  b = 3;
  visible = vis;
  state = 0;

  // Set boundaries
  value = _val;
  minv = _min;
  maxv = _max;
  step = _step;
  delta = 0;

  mleft = false;
  mmiddle = false;
  mright = false;
}

void Wheel::Render(void) {
  if (!visible)
    return;
  glPushMatrix();

  // Draw basic box (temporal)
  glBegin(GL_LINE_LOOP);
  glColor3f(0.5f, 0.5f, 0.5f);
  glVertex3f(x, y, z);
  glVertex3f(x + w, y, z);
  glVertex3f(x + w, y + h, z);
  glVertex3f(x, y + h, z);
  glEnd();

  // Draw inner box
  glBegin(GL_LINE_LOOP);
  if (state == 0)
    glColor3f(0.5f, 0.5f, 0.5f);
  if (state == 1)
    glColor3f(0.4f, 0.4f, 0.4f);
  if (state == 2)
    glColor3f(0.8f, 0.8f, 0.8f);
  glVertex3f(x + b, y + b, z);
  glVertex3f(x + w - b, y + b, z);
  glVertex3f(x + w - b, y + h - b, z);
  glVertex3f(x + b, y + h - b, z);
  glEnd();

  // Draw lines
  glBegin(GL_QUAD_STRIP);
  glColor3f(0.2f, 0.2f, 0.2f);
  glVertex3f(x + w / 2, y + b, z - 0.01f);
  glVertex3f(x + w / 2, y + h - b, z - 0.01f);
  for (int i = 0; i < 9; i++) {
    glColor3d(cos((10 * i) * PI180) * cos((10 * i) * PI180) * 0.2,
              cos((10 * i) * PI180) * cos((10 * i) * PI180) * 0.2,
              cos((10 * i) * PI180) * cos((10 * i) * PI180) * 0.2);
    glVertex3d(x + w / 2 + (w / 2 - b) * sin((10 * i) * PI180), y + b,
               z - 0.01f);
    glVertex3d(x + w / 2 + (w / 2 - b) * sin((10 * i) * PI180), y + h - b,
               z - 0.01f);
  }
  glEnd();
  glBegin(GL_QUAD_STRIP);
  glColor3f(0.2f, 0.2f, 0.2f);
  glVertex3f(x + w / 2, y + b, z - 0.01f);
  glVertex3f(x + w / 2, y + h - b, z - 0.01f);
  for (int i = 0; i < 9; i++) {
    glColor3d(cos((10 * i) * PI180) * cos((10 * i) * PI180) * 0.2,
              cos((10 * i) * PI180) * cos((10 * i) * PI180) * 0.2,
              cos((10 * i) * PI180) * cos((10 * i) * PI180) * 0.2);
    glVertex3d(x + w / 2 - (w / 2 - b) * sin((10 * i) * PI180), y + b,
               z - 0.01f);
    glVertex3d(x + w / 2 - (w / 2 - b) * sin((10 * i) * PI180), y + h - b,
               z - 0.01f);
  }
  glEnd();

  // Draw lines
  glBegin(GL_LINES);
  if (state == 0)
    glColor3f(0.5f, 0.5f, 0.5f);
  if (state == 1)
    glColor3f(0.4f, 0.4f, 0.4f);
  if (state == 2)
    glColor3f(0.8f, 0.8f, 0.8f);
  for (int i = 0; i < 9; i++) {
    glVertex3d(x + w / 2 + (w / 2 - b) * sin((10 * i + delta) * PI180), y + b,
               z);
    glVertex3d(x + w / 2 + (w / 2 - b) * sin((10 * i + delta) * PI180),
               y + h - b, z);
    glVertex3d(x + w / 2 - (w / 2 - b) * cos((10 * i + delta) * PI180), y + b,
               z);
    glVertex3d(x + w / 2 - (w / 2 - b) * cos((10 * i + delta) * PI180),
               y + h - b, z);
  }
  glEnd();

  glPopMatrix();
}

int Wheel::LDown(float xpos, float ypos) {
  if (!visible)
    return 0;
  if ((xpos >= (x + b)) && (xpos <= (x + w - b)) && (ypos >= (y + b)) &&
      (ypos <= (y + h - b))) {
    mleft = true;
    state = 1;
    x0 = xpos;
    SetCursor(LoadCursor(NULL, IDC_HAND));
  }
  return 0;
}

int Wheel::LUp(float xpos, float ypos) {
  if (!visible)
    return 0;
  if ((xpos >= (x + b)) && (xpos <= (x + w - b)) && (ypos >= (y + b)) &&
      (ypos <= (y + h - b))) {
    state = 2;
  } else {
    state = 0;
  }
  mleft = false;
  return 0;
}

int Wheel::Over(float xpos, float ypos, bool lmb) {
  if (!visible)
    return 0;
  if (!mleft && lmb)
    return 0;
  int res = 0;
  if ((xpos >= (x + b)) && (xpos <= (x + w - b)) && (ypos >= (y + b)) &&
      (ypos <= (y + h - b))) {
    SetCursor(LoadCursor(NULL, IDC_HAND));
    if (mleft)
      state = 1;
    else
      state = 2;
  } else {
    if (mleft) {
      state = 1;
      SetCursor(LoadCursor(NULL, IDC_HAND));
    } else
      state = 0;
  }
  if (mleft) {
    float dx = xpos - x0;
    delta += dx * 0.5f;
    if (delta > 10)
      delta = 0;
    if (delta < -10)
      delta = 0;
    value += dx * step;
    if (value < minv)
      value = minv;
    if (value > maxv)
      value = maxv;
    x0 = xpos;
    res = 1;
  }
  return res;
}

//-----------------------------------------------
// Tabs
//-----------------------------------------------
Tabs::Tabs(void) {
  x = 0;
  y = 0;
  z = 0;
  w = 50;
  h = 20;
  b = 5;

  // Draw control
  visible = true;
  state = 0;
  text = NULL;
  // Tabs draw control
  twidth = 80;
  theight = 25;

  mleft = false;
  mmiddle = false;
  mright = false;
}

Tabs::Tabs(float xpos, float ypos, float zpos, float width, float height,
           bool vis, int numtabs) {
  x = xpos;
  y = ypos;
  z = zpos;
  w = width;
  h = height;
  b = 5;
  visible = vis;
  state = 0;
  // Tabs draw control
  twidth = 50;
  theight = 25;

  // Tabs
  if (numtabs > 0) {
    char aux[32];
    for (int i = 0; i < numtabs; i++) {
      sprintf(aux, "tab %d", i);
      AddTab(aux);
    }
    current_tab = 0;
  }

  mleft = false;
  mmiddle = false;
  mright = false;
}

void Tabs::AddTab(const char *tname) {
  size_t len = sizeof(tname);
  TabNames.push_back(new char[len]);
  size_t pos = TabNames.size() - 1;
  memcpy((void *)&TabNames[pos], (const void *)&tname, len);
  vector<void *> tmp;
  TabFrameControls.push_back(tmp);
}

void Tabs::ShowTabControls(void) {
  for (unsigned int i = 0; i < TabFrameControls.size(); i++) {
    if (current_tab != i)
      for (unsigned int j = 0; j < TabFrameControls[i].size(); j++)
        ((Control *)TabFrameControls[i][j])->visible = false;
  }
  for (unsigned j = 0; j < TabFrameControls[current_tab].size(); j++)
    ((Control *)TabFrameControls[current_tab][j])->visible = true;
}

void Tabs::AddTabControl(int tab, void *control) {
  if (tab < 0)
    return;
  if (TabFrameControls.empty())
    return;
  TabFrameControls[tab].push_back(control);
}

void Tabs::Render(void) {
  if (!visible)
    return;

  glPushMatrix();
  glTranslatef(x, y, 0);

  // FILL
  // Filling content area
  glColor3f(0.05f, 0.05f, 0.05f);
  glBegin(GL_POLYGON);
  glVertex3f(0, theight, 0);
  glVertex3f(0, h, 0);
  glVertex3f(0, h, 0);
  glVertex3f(w - b, h, 0);
  glVertex3f(w - b, h, 0);
  glVertex3f(w, h - b, 0);
  glVertex3f(w, h - b, 0);
  glVertex3f(w, theight, 0);
  glEnd();
  // Filling tabs area
  for (unsigned int i = 0; i < TabNames.size(); i++) {
    if (current_tab != i) {
      if (mousein != i)
        glColor3f(0.15f, 0.15f, 0.15f);
      else
        glColor3f(0.25f, 0.25f, 0.25f);
    } else
      glColor3f(0.05f, 0.05f, 0.05f);
    glBegin(GL_POLYGON);
    glVertex3f(twidth * i, b, 0);
    glVertex3f(twidth * i + b, 0, 0);
    glVertex3f(twidth * (i + 1), 0, 0);
    glVertex3f(twidth * (i + 1), theight, 0);
    glVertex3f(twidth * i, theight, 0);
    glEnd();
  }
  // END OF FILLING

  // BORDERS
  glColor3f(0.5f, 0.5f, 0.5f);
  glBegin(GL_LINES);
  // Divisor between tabs and content
  glVertex3f(0, theight, 0.01f);
  glVertex3f(0 + twidth * current_tab, theight, 0.01f);
  glVertex3f(0 + twidth * (current_tab + 1), theight, 0.01f);
  glVertex3f(w, theight, 0.01f);
  // Content outer border
  glVertex3f(0, theight, 0.01f);
  glVertex3f(0, h, 0.01f);
  glVertex3f(0, h, 0.01f);
  glVertex3f(w - b, h, 0.01f);
  glVertex3f(w - b, h, 0.01f);
  glVertex3f(w, h - b, 0.01f);
  glVertex3f(w, h - b, 0.01f);
  glVertex3f(w, theight, 0.01f);
  glEnd();
  // Content region
  glColor3f(0.5f, 0.5f, 0.5f);
  glBegin(GL_LINE_LOOP);
  glVertex3f(b, theight + b, 0.01f);
  glVertex3f(w - b, theight + b, 0.01f);
  glVertex3f(w - b, h - b, 0.01f);
  glVertex3f(b, h - b, 0.01f);
  glEnd();
  // Borders of tabs area
  for (unsigned int i = 0; i < TabNames.size(); i++) {
    glBegin(GL_LINES);
    glVertex3f(twidth * i, b, 0.01f);
    glVertex3f(twidth * i + b, 0, 0.01f);

    glVertex3f(twidth * i + b, 0, 0.01f);
    glVertex3f(twidth * (i + 1), 0, 0.01f);

    glVertex3f(twidth * (i + 1), 0, 0.01f);
    glVertex3f(twidth * (i + 1), theight, 0.01f);

    glVertex3f(twidth * i, b, 0.01f);
    glVertex3f(twidth * i, theight, 0.01f);
    glEnd();
  }
  // END OF BORDERS

  // DRAW TAB TEXT
  for (unsigned int i = 0; i < TabNames.size(); i++) {
    glColor3f(0.8f, 0.8f, 0.8f);
    char aux[64];
    memset(aux, 0, 64);
    sprintf(aux, "%s", TabNames[i]);
    glRasterPos3f(twidth * i + b, y + theight - b * 2, 0.01f + z);
    glPushAttrib(GL_LIST_BIT);
    glListBase(font - 32);
    glCallLists((GLsizei)64, GL_UNSIGNED_BYTE, aux);
    glPopAttrib();
  }

  glPopMatrix();
}

int Tabs::LDown(float xpos, float ypos) {
  if (!visible)
    return 0;
  int insideof = -1;
  // Test each tab selector region
  for (unsigned int i = 0; i < TabNames.size(); i++) {
    if ((xpos >= (x + twidth * i)) && (xpos <= (x + twidth * (i + 1))) &&
        (ypos >= (y)) && (ypos <= (y + theight))) {
      insideof = i;
    }
  }
  // If mouse is over any tab but currnet one can be clicked but not changed
  // until mouse button is released
  if ((insideof != -1) && (insideof != current_tab)) {
    mleft = true;
  }
  return 0;
}

int Tabs::LUp(float xpos, float ypos) {
  if (!visible)
    return 0;
  int insideof = -1;
  int res = 0;
  // Test each tab selector region
  for (unsigned int i = 0; i < TabNames.size(); i++) {
    if ((xpos >= (x + twidth * i)) && (xpos <= (x + twidth * (i + 1))) &&
        (ypos >= (y)) && (ypos <= (y + theight))) {
      insideof = i;
    }
  }
  // Now if mouse button was released inside a tab (selector region) can be
  // selected this tab
  if ((insideof != -1) && (insideof != current_tab) && (mleft)) {
    current_tab = insideof;
    res = 1;
  }
  mleft = false;
  // After all that, show all controls from newly selected tab
  ShowTabControls();
  return res;
}

int Tabs::Over(float xpos, float ypos, bool lmb) {
  if (!visible)
    return 0;
  if (lmb && !mleft)
    return 0;
  int res = 0;
  int insideof = -1;
  // Test each tab selector region
  for (unsigned int i = 0; i < TabNames.size(); i++) {
    if ((xpos >= (x + twidth * i)) && (xpos <= (x + twidth * (i + 1))) &&
        (ypos >= (y)) && (ypos <= (y + theight))) {
      insideof = i;
    }
  }
  if ((insideof != -1) && (insideof != current_tab)) {
    state = 1;
    mousein = insideof;
    res = 1;
  } else {
    state = 0;
    mousein = -1;
  }
  return res;
}
