#include "BicubicHermiteCompositeCurves.h"
#include "BicubicHermiteArc3.h"
#include <cstddef>
#include <cmath>

using namespace std;
using namespace cagd;

BicubicHermiteCompositeCurve3::ArcAttributes::ArcAttributes(): arc(nullptr), image(nullptr), color(nullptr), previous(nullptr), next(nullptr),
                                                                previous_connection_type(LEFT), next_connection_type(RIGHT)
{}

BicubicHermiteCompositeCurve3::ArcAttributes::ArcAttributes(const ArcAttributes &a):
    arc(a.arc ? new BicubicHermiteArc3 (*a.arc) : nullptr),
    image(a.image ? new GenericCurve3(*a.image) : nullptr),
    color(a.color ? new Color4(*a.color) : nullptr),
    previous(a.previous), next(a.next),
    previous_connection_type(a.previous_connection_type), next_connection_type(a.next_connection_type)
{}


BicubicHermiteCompositeCurve3::ArcAttributes& BicubicHermiteCompositeCurve3::ArcAttributes::operator =(const ArcAttributes &a)
{
    if (this != &a)
    {
        if (arc)
        {
            delete arc; arc = nullptr;
        }

        if (image)
        {
            delete image; image = nullptr;
        }

        arc = a.arc ? new BicubicHermiteArc3 (*a.arc) : nullptr;
        image = a.image ? new GenericCurve3(*a.image) : nullptr;
        color= a.color ? new Color4(*a.color) : nullptr;
        previous = a.previous;
        next = a.next;
        previous_connection_type = a.previous_connection_type;
        next_connection_type = a.next_connection_type;

    }
    return *this; 
    
}

BicubicHermiteCompositeCurve3::ArcAttributes::~ArcAttributes()
{
    if (arc)
    {
        delete arc; arc = nullptr;
    }

    if (image)
    {
        delete image; image = nullptr;
    }

    if (previous)
    {
        previous = nullptr;
    }

    if (next)
    {
        next = nullptr;
    }

    if (color)
    {
        color = nullptr;
    }
}

BicubicHermiteCompositeCurve3::BicubicHermiteCompositeCurve3(GLuint minimal_arc_count_to_be_reserved)
{
    _attributes.reserve(minimal_arc_count_to_be_reserved);
}

// Masolo konstruktor, nem lenne ez epp olyan veszelyes
// BicubicHermiteCompositeCurve3::BicubicHermiteCompositeCurve3(BicubicHermiteCompositeCurve3 &bhcc)
// {

// }

// megkell adni:
// p0, p1, t0, t1, es ezekkel az adatokkal szepen legeneralunk egy BicubicHermiteArc3-ot
// Ennek az ujonnan generalt gorbenek szepen ujra fogjuk foglalni (boviteni) az ArcAttributes-ban levo adattagokat (pl: BicubicHermiteArc3, GenericCurve3, Color4, stb...)
GLboolean BicubicHermiteCompositeCurve3::InsertNewArc(GLuint maximum_order_of_derivatives, GLuint point_count, GLenum usage_flag, 
    const DCoordinate3 corner1, const DCoordinate3 corner2, const DCoordinate3 tangent1, const DCoordinate3 tangent2)
{
    size_t attribute_count = _attributes.size();
    static double dx = 0.0;

    if (attribute_count)
    {
        ArcAttributes *old_address = &_attributes[0];
        _attributes.resize(attribute_count+1);
        ArcAttributes *new_address = &_attributes[0];
        size_t offset = new_address - old_address;
        if (offset)
        {
            for (size_t i =0; i<attribute_count; ++i)
            {
                if(_attributes[i].previous)
                    _attributes[i].previous += offset;
                if(_attributes[i].next)
                    _attributes[i].next += offset;
            }
        }
        _attributes[attribute_count].arc = new BicubicHermiteArc3();
        // check for ptr validity
        BicubicHermiteArc3 &arc = *_attributes[attribute_count].arc; // IDE KELL DEFAULT ARC LEHET
        
        if (corner1[0] || corner1[1] || corner1[2] || corner2[0] || corner2[1] || corner2[2] ||
            tangent1[0] || tangent1[1] || tangent1[2] || tangent2[0] || tangent2[1] || tangent2[2])
        {
            arc.SetCorner(0, corner1);
            arc.SetCorner(1, corner2);
            arc.SetTangent(0, tangent1);
            arc.SetTangent(1, tangent2);
            dx -= 2.25;
        }
        else
        {
            arc.SetCorner(0, DCoordinate3(-1.0, 0.0, 0.0));
            arc.SetCorner(1, DCoordinate3(1.0, 0.0, 0.0));
            arc[0][0] += dx;
            arc[1][0] += dx;


            arc.SetTangent(0, DCoordinate3(-1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX,
                                        -1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX,
                                        0));
            arc.SetTangent(1, DCoordinate3(-1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX,
                                        -1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX,
                                        0));
        }

        arc.UpdateVertexBufferObjectsOfData();
//        _attributes[attribute_count].image = new GenericCurve3(2, 200, GL_STATIC_DRAW);
        _attributes[attribute_count].image = arc.GenerateImage(maximum_order_of_derivatives, point_count, usage_flag);
        // check for ptr validity
        GenericCurve3 &image = *_attributes[attribute_count].image;
        image.UpdateVertexBufferObjects();
        _attributes[attribute_count].color = new Color4(((GLfloat) rand() / (RAND_MAX)),
                                                        ((GLfloat) rand() / (RAND_MAX)),
                                                        ((GLfloat) rand() / (RAND_MAX)));

    }
    else
    {
//        DCoordinate3 &cp = curve[0];

        _attributes.resize(1);
        _attributes[0].arc = new BicubicHermiteArc3();
        BicubicHermiteArc3 &arc = *_attributes[0].arc; // IDE KELL DEFAULT ARC LEHET
        arc.SetCorner(0, DCoordinate3(-1.0, 0.0, 0.0));
        arc.SetCorner(1, DCoordinate3(1.0, 0.0, 0.0));
        arc[0][0] += dx;
        arc[1][0] += dx;
        arc.SetTangent(0, DCoordinate3(0.0, 2.0, 0.0));
        arc.SetTangent(1, DCoordinate3());

        arc.UpdateVertexBufferObjectsOfData();
        _attributes[0].image = arc.GenerateImage(maximum_order_of_derivatives, point_count, usage_flag);
        // check for ptr validity
        GenericCurve3 &image = *_attributes[0].image;
        image.UpdateVertexBufferObjects();
        _attributes[0].color = new Color4(((GLfloat) rand() / (RAND_MAX)),
                                                        ((GLfloat) rand() / (RAND_MAX)),
                                                        ((GLfloat) rand() / (RAND_MAX)));

    }
    
    dx += 2.25;
    return GL_TRUE;
}

GLboolean BicubicHermiteCompositeCurve3::SetDerivativeScale(GLuint index, GLdouble res)
{
    if (index >= _attributes.size())
        return GL_FALSE;

    _attributes[index].image->UpdateVertexBufferObjects(res);

    return GL_TRUE;
}

// Ezt kivalasztott indexu gorbet az ArcAttributes-bol szepen kitoroljuk, vagy csak siman ujra resize-oljuk (csokkentjuk a dimenzioit)
GLboolean BicubicHermiteCompositeCurve3::DeleteExistingArc(GLuint index)
{
    size_t attribute_count = _attributes.size();
    if (index >= attribute_count)
    {
        return GL_FALSE;
    }

    if (attribute_count)
    {
        if (_attributes[index].previous)
        {
            _attributes[index].previous->next->next_connection_type = 0;
            _attributes[index].previous->next = nullptr;
            _attributes[index].previous = nullptr;
        }
        if (_attributes[index].next)
        {
            _attributes[index].next->previous->previous_connection_type = 0;
            _attributes[index].next->previous = nullptr;
            _attributes[index].next = nullptr;
        }

        size_t last = attribute_count - 1;

        if (index == last)
        {
            _attributes.pop_back();
        }
        else
        {
            ArcAttributes *previous = _attributes[last].previous;
            ArcAttributes *next = _attributes[last].next;

            swap(_attributes[index], _attributes[last]);

            _attributes[index].arc->UpdateVertexBufferObjectsOfData();
            _attributes[index].image->UpdateVertexBufferObjects();

            _attributes.pop_back();
            if (previous)
            {
                previous->next = &_attributes[index];
            }

            if (next)
            {
                next->previous = &_attributes[index];
            }
        }

        return GL_TRUE;
    }
    else
    {
        return GL_FALSE;
    } 
}

GLboolean BicubicHermiteCompositeCurve3::ContinueExisitingArc(GLuint index, GLuint direction)
{    
    if (_attributes.size() <= index)
        return GL_FALSE;
    // hibakezeles
    if (_attributes[index].next && direction)
        return GL_FALSE;

    if (_attributes[index].previous && !direction)
        return GL_FALSE;

    DCoordinate3 tangent = _attributes[index].arc[0][direction + 2];

    // Jobb oldalra bovites
    if (direction)
    {
        InsertNewArc(2, 200, GL_STATIC_DRAW, _attributes[index].arc[0][direction],
            _attributes[index].arc[0][direction] + _attributes[index].arc[0][direction] - _attributes[index].arc[0][(direction + 1) % 2],
            tangent, tangent);
    }
    else
    {
        InsertNewArc(2, 200, GL_STATIC_DRAW,
                _attributes[index].arc[0][direction] + _attributes[index].arc[0][direction] - _attributes[index].arc[0][(direction + 1) % 2],
                _attributes[index].arc[0][direction],
                tangent, tangent);
    }

    if (direction)
    {
        _attributes[index].next = &_attributes[_attributes.size() - 1];
        _attributes[index].next_connection_type = direction;

        _attributes[_attributes.size() - 1].previous = &_attributes[index];
        _attributes[_attributes.size() - 1].previous_connection_type = 0;
    }
    else    // Balra
    {
        _attributes[index].previous = &_attributes[_attributes.size() - 1];
        _attributes[index].previous_connection_type = direction;

        _attributes[_attributes.size() - 1].next = &_attributes[index];
        _attributes[_attributes.size() - 1].next_connection_type = 1;
    }

    _attributes[_attributes.size() - 1].color = new Color4(((GLfloat) rand() / (RAND_MAX)),
                                                    ((GLfloat) rand() / (RAND_MAX)),
                                                    ((GLfloat) rand() / (RAND_MAX)));

    return GL_TRUE;
}

// ket gorbebol csinalunk egyet (meg nem tudom a hatterben leforgo matrix alakitasokat)
// Annyit tudok hogy ha a gorbe[index_0] es a gorbe[index_1] szeretnenk osszekapcsolni, akkor
// a ket gorbe koze megegyet kell generalni, aminek az egyik pontja a bal/jobb pontja (es derivaltja) kell legyen,
//                                           a masik pedig jobb/bal pontja es megfelelo derivaltja kell legyen (siman meghivjuk az InsertNewArc-ot)
GLboolean BicubicHermiteCompositeCurve3::JoinExistingArcs(GLuint index_0, GLuint direction_0, GLuint index_1, GLuint direction_1)
{
    if (index_0 >= _attributes.size() || index_1 >= _attributes.size() || index_0 == index_1)
    {
        cout << "Spinbox erteke tul nagy";
        return GL_FALSE;
    }

    // Nem nezzuk meg hogy bal vagy jobb oldali elemet kotunk, ezert tud egy bal oldali pont 3-at kotni
//    if (_attributes[index_0].previous && !direction_0)
//        return GL_FALSE;

    if (_attributes[index_0].next)
        return GL_FALSE;

    // Itt meg nem tudom de lehet hasonlo lesz a felsohoz
    if (_attributes[index_1].previous)
        return GL_FALSE;


    DCoordinate3 tangent0;
    DCoordinate3 tangent1;

    tangent0 = GetTangentCoordinates(index_0, direction_0);
    tangent1 = GetTangentCoordinates(index_1, direction_1);

    // Left left kapcsolat
    if(!direction_0)
    {
        tangent0  *= -1.0;
    }

    if (direction_1)
    {
        tangent1 *= -1.0;
    }

    InsertNewArc(   2, 100, GL_STATIC_DRAW,
                    GetPointCoordinates(index_0, direction_0),
                    GetPointCoordinates(index_1, direction_1),
                    tangent0,
                    tangent1);

    _attributes[index_0].next = &_attributes[_attributes.size() - 1];
    _attributes[index_0].next_connection_type = direction_0;

    _attributes[index_1].previous = &_attributes[_attributes.size()-1];
    _attributes[index_1].previous_connection_type = direction_1;

    _attributes[_attributes.size()-1].previous = &_attributes[index_0];
    _attributes[_attributes.size()-1].previous_connection_type = 0;
    _attributes[_attributes.size()-1].next = &_attributes[index_1];
    _attributes[_attributes.size()-1].next_connection_type = 1;

    _attributes[_attributes.size() - 1].color = new Color4(((GLfloat) rand() / (RAND_MAX)),
                                                    ((GLfloat) rand() / (RAND_MAX)),
                                                    ((GLfloat) rand() / (RAND_MAX)));


    return GL_TRUE;
}

// Negy pontbol kivesszuk a ket kozbulsot es azok derivaltjait es huss, ujra generaljuk a gorbet (kell kicsinyiteni a memoriat)
GLboolean BicubicHermiteCompositeCurve3::MergeExistingArcs(GLuint index_0, GLuint direction_0, GLuint index_1, GLuint direction_1)
{
    if (index_0 >= _attributes.size() || index_1 >= _attributes.size() || index_0 == index_1)
        return GL_FALSE;
    // Hibekezeles ha nem tudunk kotni mar vagy mozgatni

    DCoordinate3 in0;
    DCoordinate3 in1;
    _attributes[index_0].arc->GetCorner(direction_0, in0);
    _attributes[index_1].arc->GetCorner(direction_1, in1);
    DCoordinate3 new_coordinate;
    DCoordinate3 new_tangent;
    DCoordinate3 tan0;
    DCoordinate3 tan1;
    _attributes[index_0].arc->GetTangent(direction_0, tan0);
    _attributes[index_1].arc->GetTangent(direction_1, tan1);
    new_tangent = tan0 + tan1;
    new_tangent *= 0.5;
    cout << new_tangent << " " << tan0 << " " << tan1 << endl;
    _attributes[index_0].arc->SetTangent(direction_0, new_tangent);


    if(direction_0 != direction_1) {
        _attributes[index_1].arc->SetTangent(direction_1, new_tangent);
    }
    else {
        _attributes[index_1].arc->SetTangent(direction_1, new_tangent*-1);
    }


    new_coordinate = in0 + in1;
    new_coordinate *= 0.5;
    _attributes[index_0].arc->SetCorner(direction_0, new_coordinate);
    _attributes[index_1].arc->SetCorner(direction_1, new_coordinate);

    BicubicHermiteArc3 &arc = *_attributes[index_0].arc;
    arc.UpdateVertexBufferObjectsOfData();
    _attributes[index_0].image = arc.GenerateImage(2, 200, GL_STATIC_DRAW);
    GenericCurve3 &image = *_attributes[index_0].image;
    image.UpdateVertexBufferObjects();

    BicubicHermiteArc3 &arc1 = *_attributes[index_1].arc;
    arc1.UpdateVertexBufferObjectsOfData();
    _attributes[index_1].image = arc1.GenerateImage(2, 200, GL_STATIC_DRAW);
    GenericCurve3 &image1 = *_attributes[index_1].image;
    image1.UpdateVertexBufferObjects();


    _attributes[index_0].next = &_attributes[index_1];
    _attributes[index_0].next_connection_type = direction_0;

    _attributes[index_1].previous = &_attributes[index_0];
    _attributes[index_1].previous_connection_type = direction_1;


    _attributes[index_0].color = new Color4(((GLfloat) rand() / (RAND_MAX)),
                                                    ((GLfloat) rand() / (RAND_MAX)),
                                                    ((GLfloat) rand() / (RAND_MAX)));
    _attributes[index_1].color = _attributes[index_0].color;
    return GL_TRUE;
}

// Kirajzolni az osszes gorbet
GLboolean BicubicHermiteCompositeCurve3::RenderAllArcs(GLuint order, GLenum render_mode)
{
    GLuint n = _attributes.size();
    for(GLuint i = 0; i < n; i++)
    {
        if(_attributes[i].image)
        {
            //glColor3fv(_attributes[i].color[0]);
            _attributes[i].image->RenderDerivatives(order, render_mode);
            _attributes[i].arc->RenderData();
        }
        else
            return GL_FALSE;
    }

    return GL_TRUE;
}

// Egy gorbet kell csak kirajzolni
GLboolean BicubicHermiteCompositeCurve3::RenderSelectedArc(GLuint index, GLuint order, GLenum render_mode) const
{
    if (index >= _attributes.size())
    {
        cout << "Spinbox erteke tul nagy";
        return GL_FALSE;
    }
    //    glColor3fv(&_arc_colors[_attributes[index].color][0]);
    _attributes[index].image->RenderDerivatives(order, render_mode);
    _attributes[index].arc->RenderData();

    return GL_TRUE;
}

void BicubicHermiteCompositeCurve3::SetPointCoordinates(GLuint index, GLuint direction, DCoordinate3 point){
    if (index >= _attributes.size())
    {
        cout << "Spinbox erteke tul nagy";
        return;
    }

    _attributes[index].arc->SetCorner(direction, point);

    if (_attributes[index].next && _attributes[index].next_connection_type == direction)
    {
        _attributes[index].next->arc->SetCorner(_attributes[index].next->previous_connection_type, point);
    }

    if (_attributes[index].previous && _attributes[index].previous_connection_type == direction)
    {
        _attributes[index].previous->arc->SetCorner(_attributes[index].previous->next_connection_type, point);
    }
}

void BicubicHermiteCompositeCurve3::SetTangentCoordinates(GLuint index, GLuint direction, DCoordinate3 point){
    if (index >= _attributes.size())
    {
        cout << "Spinbox erteke tul nagy";
        return;
    }

    DCoordinate3 old_point_value = GetTangentCoordinates(index, direction);
    _attributes[index].arc->SetTangent(direction, point);

    if (_attributes[index].next && _attributes[index].next_connection_type == direction)
    {

        DCoordinate3 old_neighbour_value;
        _attributes[index].next->arc->GetTangent(_attributes[index].next->previous_connection_type, old_neighbour_value);

        cout << "Kovi: " << old_point_value << " " << old_neighbour_value << endl;

        if (old_point_value.x() != old_neighbour_value.x() || old_point_value.y() != old_neighbour_value.y() || old_point_value.z() != old_neighbour_value.z())
        {
            cout << " itt\n";
            _attributes[index].next->arc->SetTangent(_attributes[index].next->previous_connection_type, -1.0 * point);
        }
        else
        {
            cout << " ott\n";
            _attributes[index].next->arc->SetTangent(_attributes[index].next->previous_connection_type, point);
        }
    }

    if (_attributes[index].previous && _attributes[index].previous_connection_type == direction)
    {
        DCoordinate3 old_neighbour_value;
        _attributes[index].previous->arc->GetTangent(_attributes[index].previous->next_connection_type, old_neighbour_value);

        cout << "Azelott: " << old_point_value << " " << old_neighbour_value << endl;

        if (old_point_value.x() != old_neighbour_value.x() || old_point_value.y() != old_neighbour_value.y() || old_point_value.z() != old_neighbour_value.z())
        {
            cout << "ITt \n";
            _attributes[index].previous->arc->SetTangent(_attributes[index].previous->next_connection_type, -1.0 * point);
        }
        else
        {
            cout <<"Ott \n";
            _attributes[index].previous->arc->SetTangent(_attributes[index].previous->next_connection_type, point);

        }
    }
}

DCoordinate3 BicubicHermiteCompositeCurve3::GetPointCoordinates(GLuint index, GLuint no){
    if (index >= _attributes.size())
    {
        cout << "Spinbox erteke tul nagy";
        return DCoordinate3();
    }

    DCoordinate3 point;
    _attributes[index].arc->GetCorner(no, point);
    return point;
}

DCoordinate3 BicubicHermiteCompositeCurve3::GetTangentCoordinates(GLuint index, GLuint no){
    if (index >= _attributes.size())
    {
        cout << "Spinbox erteke tul nagy";
        return DCoordinate3();
    }

    DCoordinate3 point;
    _attributes[index].arc->GetTangent(no, point);
    return point;
}

void BicubicHermiteCompositeCurve3::UpdateArcs(GLuint index) {
    if (index >= _attributes.size())
    {
        cout << "Spinbox erteke tul nagy";
        return;
    }

    for (GLuint i = 0; i < _attributes.size(); ++i)
    {
        _attributes[i].arc->DeleteVertexBufferObjectsOfData();
        _attributes[i].image->DeleteVertexBufferObjects();

        BicubicHermiteArc3 &arc = *_attributes[i].arc;
        arc.UpdateVertexBufferObjectsOfData();
        _attributes[i].image = arc.GenerateImage(2, 100, GL_STATIC_DRAW);
        GenericCurve3 &image = *_attributes[i].image;
        image.UpdateVertexBufferObjects();
    }
}
