#include <TemplateApp.h>



//8x8 RGB Bitmap. Use AWTRIX BMPdrawer to easily create a bitmap (https://github.com/Blueforcer/AWTRIX/tree/master/BMPdrawer)
static const uint16_t sun[]PROGMEM  {0x0, 0x0, 0xffe9, 0x0, 0x0, 0xffe9, 0x0, 0x0, 0xffe9, 0x0, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0x0, 0xffe9, 0x0, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0x0, 0x0, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0x0, 0x0, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0x0, 0x0, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0x0, 0xffe9, 0x0, 0xffe9, 0xffe9, 0xffe9, 0xffe9, 0x0, 0xffe9, 0x0, 0x0, 0xffe9, 0x0, 0x0, 0xffe9, 0x0, 0x0 };
String templateString "Its Working";

void TemplateApp::render(DisplayManager& display) {
    // Called in loop when the app is active. Use GFX functions to display your App.
    // see DisplayManager.h for all possible functions.
    // The following function combines all the calls required to display an app.

    display.drawApp(sun, templateString, {0,0}, {255, 255, 255}, true, 40, 200);
    //RGBbmp,text to display,{X,Y Textposition},Textcolor, Autoscroll, scrolldelay (lower=faster), Delay for next scroll
}


void TemplateApp::enable() {
    // Is called up once every time the app is started

}


void TemplateApp::update() {
    // Is called after "UpdateThreshold". Here you can fetch your nessesary data

}
