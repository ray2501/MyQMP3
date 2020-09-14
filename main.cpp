#include "mainwindow.h"

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);  
    
  MainWindow window;

  window.setWindowTitle("MyQMP3");
  window.show();

  return app.exec();
}
