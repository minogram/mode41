#include "PtnMainWindow.h"
#include "DxfSceneBuilder.h"
#include "DxfPtnConvert.h"
#include "PtnSceneBuilder.h"
#include "DxfReader.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QPrinter>
#include <QPrintDialog>
#include <QException>
#include <QDebug>

#include "wykobi.hpp"
#include "wykobi_algorithm.hpp"

void PtnMainWindow::test1()
{
    // segment intersection
    const std::size_t max_segments = 100;
    std::vector<wykobi::segment<double, 2>> segment_list;

    double width = 1000;
    double height = 1000;
    for(std::size_t i = 0; i < max_segments; ++i)
    {
       wykobi::segment<double, 2> tmp_segment;
       wykobi::generate_random_object(0.0,0.0,width,height,tmp_segment);
       segment_list.push_back(tmp_segment);
    }

    std::vector<wykobi::point2d<double>> intersection_list;
    wykobi::algorithm::naive_group_intersections<wykobi::segment<double, 2>>(segment_list.begin(),
                                                               segment_list.end(),
                                                               std::back_inserter(intersection_list));

    // draw segments
    qDebug() << intersection_list.size();
    QPen pen;
    pen.setColor(QColor(254,23,99));
    pen.setWidth(2);
    pen.setCosmetic(true);
    foreach (auto seg, segment_list) {
        m_scene->addLine(seg[0].x, seg[0].y, seg[1].x, seg[1].y, pen);
    }

    // draw intersections
    QPen pen2;
    pen2.setColor(QColor(254,200,80));
    pen2.setWidth(1);
    pen2.setCosmetic(true);
    foreach (auto i, intersection_list) {
        m_scene->addLine(i.x-2, i.y-2, i.x+2, i.y+2, pen2);
        m_scene->addLine(i.x-2, i.y+2, i.x+2, i.y-2, pen2);
    }

//    std::for_each(intersection_list.begin(), intersection_list.end(),
//                  [] (wykobi::point2d<double> &i) { qDebug() << i.x << i.y; });

//    const std::size_t bezier_count = 15;
//    const std::size_t resolution   = 1000;
//    std::vector<wykobi::cubic_bezier<T,2>> bezier_list;

//    for(std::size_t i = 0; i < bezier_count; ++i)
//    {
//       wykobi::cubic_bezier<T,2> bezier;
//       bezier[0] = wykobi::generate_random_point<T>(width,height);
//       bezier[1] = wykobi::generate_random_point<T>(width,height);
//       bezier[2] = wykobi::generate_random_point<T>(width,height);
//       bezier[3] = wykobi::generate_random_point<T>(width,height);
//       bezier_list.push_back(bezier)
//    }

//    for(std::size_t i = 0; i < bezier_list.size(); ++i)
//    {
//       std::vector<point2d<T>> point_list;
//       wykobi::generate_bezier(bezier_list[i],resolution,point_list);
//       draw_polyline(point_list);
//    }
}

void PtnMainWindow::test2()
{
    // segment intersection
    const std::size_t max_segments = 100;
    std::vector<wykobi::segment<double, 2>> segment_list;

    double width = 1000;
    double height = 1000;
    for(std::size_t i = 0; i < max_segments; ++i)
    {
       wykobi::segment<double, 2> tmp_segment;
       wykobi::generate_random_object(0.0,0.0,width,height,tmp_segment);
       segment_list.push_back(tmp_segment);
    }

//    std::vector<wykobi::point2d<double>> intersection_list;
//    wykobi::algorithm::naive_group_intersections<wykobi::segment<double, 2>>(segment_list.begin(),
//                                                               segment_list.end(),
//                                                               std::back_inserter(intersection_list));

    // draw segments
    QPen pen;
    pen.setColor(QColor(254,23,99));
    pen.setWidth(2);
    pen.setCosmetic(true);
    foreach (auto seg, segment_list) {
        m_scene->addLine(seg[0].x, seg[0].y, seg[1].x, seg[1].y, pen);
    }

    wykobi::point2d<double> pick;
    pick.x = 500;
    pick.y = 500;
    pen.setColor(Qt::yellow);
    foreach (auto seg, segment_list) {
        auto closed = wykobi::closest_point_on_segment_from_point(seg, pick);
        m_scene->addLine(pick.x, pick.y, closed.x, closed.y, pen);


//        wykobi::point2d<T> closest_point = wykobi::closest_point_on_segment_from_point(segment,point_list[i]);

//         if (wykobi::distance(closest_point,point_list[i]) > T(1.0))
//         {
//            graphic.draw(wykobi::make_segment(closest_point,point_list[i]));
//         }
//         graphic.draw_circle(point_list[i],3);
//         graphic.draw_circle(closest_point,2);
    }
}

void PtnMainWindow::test3()
{
}

