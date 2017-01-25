#include "HexViewWindow.h"

#include <QToolBar>
#include <QAction>
#include <QFileDialog>
#include <QScrollArea>
#include <QMessageBox>
#include <QFile>
#include <QByteArray>
#include <QSettings>
#include <QMenu>
#include <QMenuBar>
#include <QInputDialog>

#include <QDebug>

#include "QHexView.h"


HexViewWindow::HexViewWindow(QWidget *parent, Qt::WindowFlags flags):
QMainWindow(parent, flags)
{
	QToolBar *ptb = addToolBar("File");


	QMenu *pmenu = menuBar() -> addMenu("&File");
	pmenu -> addAction("Go to offset...", this, SLOT(slotToOffset()));
	pmenu -> addAction("Exit", this, SLOT(close()));

	QHexView *pwgt = new QHexView;
	setCentralWidget(pwgt);

	readCustomData();
}


void HexViewWindow::process(const QString &fileName)
{
	QFile file(fileName);


	if(!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::critical(this, "File opening problem", "Problem with open file `" + fileName + "`for reading");
		return;
	}

	QHexView *pcntwgt = dynamic_cast<QHexView *>(centralWidget());

	pcntwgt -> clear();

	QByteArray arr = file.readAll();
	pcntwgt -> setData(new QHexView::DataStorageArray(arr));

}

void HexViewWindow::setData(char *buffer, int size) {
    QHexView *pcntwgt = dynamic_cast<QHexView *>(centralWidget());

    QByteArray arr = QByteArray(buffer, size);
    pcntwgt -> setData(new QHexView::DataStorageArray(arr));

}

void HexViewWindow::slotToOffset()
{
	bool ok;
	int offset = QInputDialog::getInt(0, "Offset", "Offset:", 0, 0, 2147483647, 1, &ok);

	if(ok)
	{
		QHexView *pcntwgt = dynamic_cast<QHexView *>(centralWidget());
		pcntwgt -> showFromOffset(offset);
	}
}


void HexViewWindow::closeEvent(QCloseEvent *pevent)
{
	saveCustomData();
	QWidget::closeEvent(pevent);
}


void HexViewWindow::saveCustomData()
{
	QSettings settings("QHexView", "QHexView");
	settings.setValue("HexViewWindow/geometry", saveGeometry());
}


void HexViewWindow::readCustomData()
{
	QSettings settings("QHexView", "QHexView");
	restoreGeometry(settings.value("HexViewWindow/geometry").toByteArray());
}

