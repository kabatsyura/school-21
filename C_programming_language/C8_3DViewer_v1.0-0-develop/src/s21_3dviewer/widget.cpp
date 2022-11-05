#include "widget.h"
#include "ui_widget.h"
#include "math.h"
#include <QMessageBox>
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QOpenGLWidget(parent)
    , ui(new Ui::Widget)

{
        setWindowTitle("the visualaze_3d_object");
        setGeometry(0,0,1050,800);
        parcing_3d_files();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::initializeGL() {
}

void Widget::resizeGL(int w, int h) {
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

//     int min = -484;
//     int max =  338;
     double min = 0.0;
     double max = 0.0;
     get_max_min_frustum(&max, &min, some_data);
     if (qFabs(min) > max) {
        max = qFabs(min);
        } else if (max > qFabs(min)) {
            min = -max;
        }
//     min*=1.2;
//     max*=1.2;
//     glOrtho(min,max,min,max,min,max);
     /* задаем параметры */
      double coef = 1.2;
//      min_x*=coef;
//      max_x*=coef;
//      min_y*=coef;
//      max_y*=coef;
//      min_z*=coef;
//      max_z*=coef;
      max *=coef;
      min *=coef;
     /* но для корректного отображения, обрати внимание, на функции в paintGL
     */
     glOrtho(min,max,min,max,min,max);
//              glOrtho(min, max, min, max, min_z, max_z+100);
//              glOrtho(max_x, min_x, max_y, min_y, min_z, max_z);
     //         glOrtho(min_x, max_x, min_y, max_y, min_z, max_z);

     /* перспектива*/
//     glTranslatef(0, 0, 10);
//      double width = max_x - min_x;
//      double height = max_y - min_y;

//      gluPerspective(60.f, (GLfloat)(width/height), 1, 5000);
//              glFrustum(min,max,min,max,min,max);

}

void Widget::paintGL() {
       if(!path_to_file.isNull()){
       vertex = (double *)calloc(some_data.count_of_vertex*3, sizeof(double));
       facets = (unsigned int *)calloc(some_data.count_of_polygons*10, sizeof(unsigned int));
       for (int i = 0, k = 0; i < some_data.matrix.rows; i++) {
           for (int j = 0; j < some_data.matrix.columns; j++, k++) {
               vertex[k] = some_data.matrix.matrix[i][j];
               if(k == 0)
               {
               min_x = vertex[k]; max_x = vertex[k];
               min_y = vertex[k]; max_y = vertex[k];
               min_z = vertex[k]; max_z = vertex[k];
               }
               else
               {
               if(k % 2 == 0) check_vertex_min_max(vertex[k], 2);
               else if(k % 3 == 0) check_vertex_min_max(vertex[k], 3);
               else check_vertex_min_max(vertex[k], 1);
               }
           }
       }
       for (int i = 0, k = 0;i < some_data.count_of_polygons ; i++) {
           for (int j = 0; j < some_data.polygons[i].numbers_of_vertexes_in_facets*2; j++, k++) {
                facets[k] = some_data.polygons[i].vertexes[j];
           }
       }

        glClearColor(r1,g1,b1,0);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotatef(xRot, 1.0, 0.0, 0.0);
        glRotatef(yRot, 0.0, 1.0, 0.0);
//        if(change_geometry) glTranslatef(0,min_y,min_z);
        if (line_type) {
            glLineStipple(1, 0x00F0);
            glEnable(GL_LINE_STIPPLE);
        } else {
            glDisable(GL_LINE_STIPPLE);
        }
         glPointSize(width);
        for (int i = 0; i < some_data.count_of_vertex + 1; i++) {
                if (type_point == 1)
                {
                    glDisable(GL_POINT_SMOOTH);
                    glDisable(GL_POINT);
                } else if (type_point == 2) {
                    glEnable(GL_POINT_SMOOTH);
                    glBegin(GL_POINT_SMOOTH);
                    glEnd();
                } else if (type_point == 3) {
                    glDisable(GL_POINT_SMOOTH);
                    glBegin(GL_POINT);
                    glEnd();
                }
            }
        glVertexPointer(3, GL_DOUBLE, 0, vertex);
        glEnableClientState(GL_VERTEX_ARRAY);
        glDrawArrays(GL_POINTS, 0, some_data.count_of_vertex);
        glLineWidth(width_edge);
        glColor4f(r, g, b, 1);
        glDrawElements(GL_POINTS, some_data.count_of_polygons * 6, GL_UNSIGNED_INT, facets);
        glColor4f(r2, g2, b2, 1);
        glDrawElements(GL_LINES, some_data.count_of_polygons * 6, GL_UNSIGNED_INT, facets);
        glDisableClientState(GL_VERTEX_ARRAY);
       }
}

void Widget::mousePressEvent(QMouseEvent* mo){
    mPos = mo->pos();
}
void Widget::mouseMoveEvent(QMouseEvent* mo){
    xRot= 1/M_PI*(mo->pos().y() - mPos.y());
    yRot= 1/M_PI*(mo->pos().x() - mPos.x());
    update();
}

int Widget::validation_of_files(char* name_file) {
    if(count_vertexes_polygons(name_file, &some_data) && !path_to_file.isNull()) { errors(3); return 1; }
    if(create_matrix_obj(name_file, &some_data) && !path_to_file.isNull()) { errors(4); return 1; }
    if(note_vertexes_polygons(name_file, &some_data) && !path_to_file.isNull()) { errors(5); return 1; }
    return 0;
}

void Widget::errors(int error) {
    switch (error) {
    case 1:
        QMessageBox::warning(this, "Внимание","File not open");
        break;
    case 2:
        QMessageBox::warning(this, "Внимание","File not exist");
        break;
    case 3:
        QMessageBox::warning(this, "Внимание","File doesnot parsed");
        break;
    case 4:
        QMessageBox::warning(this, "Внимание","File doesnot create_matrix_obj");
        break;
    case 5:
        QMessageBox::warning(this, "Внимание","File doesnot note_vertexes_polygons");
        break;
    default:
        break;
    }

}

void Widget:: parcing_3d_files()
{
    path_to_file = QFileDialog::getOpenFileName(NULL, "Open", "/Users/", "*.obj");
    QByteArray tmp = path_to_file.toLocal8Bit();
    char* name_of_file = tmp.data();

    if (!name_of_file) { errors(2); path_to_file = NULL; return; }
    if  (validation_of_files(name_of_file)) { path_to_file = NULL; return;}

}

void Widget:: check_vertex_min_max(double check, int choise) {

    switch (choise) {
    case 1:
        if(std::less<double>{}(max_x, check)) max_x = check;
        if(std::greater<double>{}(min_x, check)) min_x = check;
        break;
    case 2:
        if(std::less<double>{}(max_y, check)) max_y = check;
        if(std::greater<double>{}(min_y, check)) min_y = check;
        break;
    case 3:
        if(std::less<double>{}(max_z, check)) max_z = check;
        if(std::greater<double>{}(min_z, check)) min_z = check;
        break;
    }
}

void Widget::for_move(double x, double y, double z)
{
    move_obj(&some_data, x, y, z);
    update();
}

void Widget::for_rot(double x, double y, double z)
{
    rotation_by_ox(&some_data, x);
    rotation_by_oy(&some_data, y);
    rotation_by_oz(&some_data, z);
    update();
}

void Widget::for_scale(double x)
{
    scale_obj(&some_data, x);
    update();
}

void Widget::change_background_color(double x, double y, double z)
{
    glClearColor(x,y,z,0);
    update();
}

void Widget::change_vertex_color(double x, double y, double z)
{
    glColor4f(x, y, z, 1);
    update();
}

void Widget::change_vertex_size(double x)
{
    glPointSize(x);
    update();
}

void Widget::change_edge_color(double x, double y, double z)
{
    glColor4f(x,y,z, 1);
    update();
}

void Widget::change_edge_size(double x)
{
    glLineWidth(x);
    update();
}
void Widget::change_line_type_1(double x)
{
    line_type = x;
    update();
}

void Widget::change_line_type_2(double x)
{
    line_type = x;
    update();
}

void Widget::change_vertex_type(double x)
{
    type_point = x;
    update();
}

void Widget::change_geo() {
    repaint();
    update();
}
