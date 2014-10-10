/****************************************************************************
**
** Copyright (C) 2014 Dinu SV.
** (contact: mail@dinusv.com)
** This file is part of Live CV application.
**
** GNU General Public License Usage
** 
** This file may be used under the terms of the GNU General Public License 
** version 3.0 as published by the Free Software Foundation and appearing 
** in the file LICENSE.GPL included in the packaging of this file.  Please 
** review the following information to ensure the GNU General Public License 
** version 3.0 requirements will be met: http://www.gnu.org/copyleft/gpl.html.
**
****************************************************************************/
#include "QMatAccess.hpp"
#include <QElapsedTimer>

using namespace cv;

QElapsedTimer timer;

namespace helpers{

template<typename T, typename LT> void cacheValues( Mat& m, QVariantList& output){
    T* data  = reinterpret_cast<T*>(m.data);
    int step = (int)(m.step / sizeof(T));
    for ( int i = 0; i < m.rows; ++i ){
        QList<LT> row;
        int rowstep = i * step;
        for ( int j = 0; j < m.cols * m.channels(); ++j ){
            row.append(data[rowstep + j]);
        }
        output.append(QVariant::fromValue(row));
    }
}

template<typename T, typename LT> void setValues( QVariantList& values, Mat& m){
    T* data  = reinterpret_cast<T*>(m.data);
    int step = (int)(m.step / sizeof(T));

    for ( int i = 0; i < m.rows; ++i ){
        QList<LT> row = values.at(i).value<QList<LT> >();
        int rowstep = i * step;
        for ( int j = 0; j < m.cols * m.channels(); ++j ){
            data[rowstep + j] = static_cast<T>(row.at(j));
        }
    }
}

}// namespace helpers

/**
 * @brief QMatAccess::QMatAccess
 * @param parent
 */
QMatAccess::QMatAccess(QQuickItem *parent)
    : QQuickItem(parent)
    , m_mat(0){
}

/**
 * @brief QMatAccess::QMatAccess
 * @param mat
 * @param parent
 */
QMatAccess::QMatAccess(QMat *mat, QQuickItem *parent)
    : QQuickItem(parent)
    , m_mat(mat){

    Mat* cvmat = m_mat->cvMat();
    m_dataPtr  = cvmat->data;
    m_channels = cvmat->channels();

}

/**
 * @brief QMatAccess::~QMatAccess
 */
QMatAccess::~QMatAccess(){
}

/**
 * @brief QMatAccess::setUpCache
 */
void QMatAccess::setUpCache(){
    Mat* cvmat = m_mat->cvMat();

    switch(cvmat->depth()){
    case CV_8U:
        helpers::cacheValues<uchar, int>(*cvmat, m_values);
        break;
    case CV_8S:
        helpers::cacheValues<uchar, int>(*cvmat, m_values);
        break;
    case CV_16U:
        helpers::cacheValues<short, int>(*cvmat, m_values);
        break;
    case CV_16S:
        helpers::cacheValues<short, int>(*cvmat, m_values);
        break;
    case CV_32S:
        helpers::cacheValues<int, int>(*cvmat, m_values);
        break;
    case CV_32F:
        helpers::cacheValues<float, float>(*cvmat, m_values);
        break;
    case CV_64F:
        helpers::cacheValues<float, qreal>(*cvmat, m_values);
        break;
    }
}

/**
 * @brief QMatAccess::values
 * @return
 */
QVariantList QMatAccess::values(){
    if ( m_values.empty() )
        setUpCache();
    return m_values;
}

/**
 * @brief QMatAccess::setValues
 * @param values
 */
void QMatAccess::setValues(QVariantList values){
    m_values = values;

    Mat* cvmat = m_mat->cvMat();
    switch(cvmat->depth()){
    case CV_8U:
        helpers::setValues<uchar, int>(m_values, *cvmat);
        break;
    case CV_8S:
        helpers::setValues<uchar, int>(m_values, *cvmat);
        break;
    case CV_16U:
        helpers::setValues<short, int>(m_values, *cvmat);
        break;
    case CV_16S:
        helpers::setValues<short, int>(m_values, *cvmat);
        break;
    case CV_32S:
        helpers::setValues<int, int>(m_values, *cvmat);
        break;
    case CV_32F:
        helpers::setValues<float, float>(m_values, *cvmat);
        break;
    case CV_64F:
        helpers::setValues<float, qreal>(m_values, *cvmat);
        break;
    }
}