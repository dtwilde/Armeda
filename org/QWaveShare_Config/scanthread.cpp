#include "scanthread.h"


ScanThread::ScanThread(QObject *parent, WS_Device * configParent) :
    QThread(parent)
{

    m_Config = configParent;
    m_stopScan = false;
}

ScanThread::~ScanThread()
{

}

void ScanThread::beginScan(int iStartRange, int iEndRange)
{

    if (!isRunning())
    {

        m_iStartRange = iStartRange;
        m_iEndRange = iEndRange;

        m_stopScan=false;
        start();

    }

}
void ScanThread::stopScan()
{
    m_stopScan=true;
}

void ScanThread::run()
{

    for(int i=m_iStartRange;i<m_iEndRange;i++)
    {

        float fVersion = 0;
        bool bResult = m_Config->ReadSoftwareVersion(i,fVersion);

        if(bResult)
        {

            emit deviceDiscovered(i);
        }

        if(m_stopScan)
           break;

    }

    emit scanComplete();
}

