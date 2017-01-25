#ifndef MAIN_WINDOW_H_
#define MAIN_WINDOW_H_

#include <QMainWindow>


class HexViewWindow : public QMainWindow {
Q_OBJECT
public:
    HexViewWindow(QWidget *parent = 0, Qt::WindowFlags flags = 0);

    void setData(char *buffer, int size);

protected:
    virtual void closeEvent(QCloseEvent *);

private:
    void process(const QString &fileName);

    void saveCustomData();

    void readCustomData();

private slots:

    void slotToOffset();
};


#endif
