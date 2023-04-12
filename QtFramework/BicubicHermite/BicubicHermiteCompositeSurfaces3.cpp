#include "BicubicHermiteCompositeSurfaces3.h"
#include "BicubicHermitePatches3.h"
#include <cstddef>
#include <fstream>
#include <iostream>

using namespace std;
using namespace cagd;

/*
BicubicHermitePatch3            *patch;
TriangulatedMesh3               *image;
Material                        *material; // use pointers to pre-defined materials
QOpenGLTexture                  *texture;  // use pointers to pre-defined textures
// ShaderProgram       *shader;   // use pointers to pre-defined shader programs

// other attributes
// ...

PatchAttributes   *neighbours[8];
Direction         connection_type[8];
*/
BicubicHermiteCompositeSurface3::PatchAttributes::PatchAttributes(): 
    patch(nullptr), image(nullptr), material(nullptr), texture(nullptr)
{
    for (GLuint i = 0;  i < 8; ++i)
    {
        connection_type[i] = 0;
        neighbours[i] = nullptr;
    }
}

BicubicHermiteCompositeSurface3::PatchAttributes::PatchAttributes(const PatchAttributes &a):
    patch(a.patch ? new BicubicHermitePatch3 (*a.patch) : nullptr),
    image(a.image ? new TriangulatedMesh3 (*a.image) : nullptr),
    material(a.material),
    texture(a.texture)
{
    for (GLuint i = 0;  i < 8; ++i)
    {
        connection_type[i] = a.connection_type[i];
        neighbours[i] = a.neighbours[i];
    }
}

BicubicHermiteCompositeSurface3::PatchAttributes& BicubicHermiteCompositeSurface3::PatchAttributes::operator =(const PatchAttributes &a)
{
    if (this != &a)
    {
        if (patch)
        {
            delete patch; patch = nullptr;
        }

        if (image)
        {
            delete image; image = nullptr;
        }

        patch = a.patch ? new BicubicHermitePatch3 (*a.patch) : nullptr;
        image = a.image ? new TriangulatedMesh3 (*a.image) : nullptr;
        material = a.material; 
        texture = a.texture;
        
        for (GLuint i = 0;  i < 8; ++i)
        {
            connection_type[i] = a.connection_type[i];
            neighbours[i] = a.neighbours[i];
        }
    }
    return *this;
}

BicubicHermiteCompositeSurface3::PatchAttributes::~PatchAttributes()
{
    if (patch)
    {
        delete patch; patch = nullptr;
    }

    if (image)
    {
        delete image; image = nullptr;
    }

    if (material)
    {
        material = nullptr;
    }

    if (texture)
    {
        texture = nullptr;
    }

    for (GLuint i = 0;  i < 8; ++i)
        neighbours[i] = nullptr;

}

BicubicHermiteCompositeSurface3::BicubicHermiteCompositeSurface3(GLuint minimial_patch_count_to_be_reserved)
{
    _attributes.reserve(minimial_patch_count_to_be_reserved);

    //    ifstream patches;
    //    patches.open("Project/patches.txt");

    //    if (!patches.is_open())
    //    {
    //        return;
    //    }

    //    GLuint count = 2;
    //    //patches >> count;

    //    _attributes.resize(count + 1);

    //    for (GLuint i = 0; i < count; ++i)
    //    {
    //        patches >> *_attributes[i].patch;
    //    }
}

// operations
GLboolean BicubicHermiteCompositeSurface3::InsertNewPatch(GLuint maximum_order_of_derivatives, GLuint u_div_point_count, GLuint v_div_point_count, GLenum usage_flag, const BicubicHermitePatch3& a)
{
    size_t attribute_count = _attributes.size();
    static double dx = 0.0;

    if (attribute_count)
    {
        PatchAttributes *old_address = &_attributes[0];
        _attributes.resize(attribute_count + 1);
        PatchAttributes *new_address = &_attributes[0];
        size_t offset = new_address - old_address;
        if (offset)
        {
            for (size_t i = 0; i < attribute_count; ++i)
            {
                for (GLuint j = 0; j < 8; ++j)
                {
                    if(_attributes[i].neighbours[j])
                        _attributes[i].neighbours[j] += offset;
                }
            }
        }

        _attributes[attribute_count].patch = new BicubicHermitePatch3();
        BicubicHermitePatch3 &patch = *_attributes[attribute_count].patch;

        GLboolean change = GL_FALSE;
        for (GLuint i = 0; i < 4 && !change; ++i) 
            for (GLuint j = 0; j < 4 && !change; ++j)
                if (a.GetMatrixValue(i, j).x() || a.GetMatrixValue(i, j).y() || a.GetMatrixValue(i, j).z())
                    change = GL_TRUE;
                

        if (change)
        {
            for (GLuint i = 0; i < 4; ++i) 
                for (GLuint j = 0; j < 4; ++j)
                    _attributes[attribute_count].patch->SetMatrixValue(i, j, a.GetMatrixValue(i, j));

            dx -= 2.25;
        }
        else
        {
            patch.SetCorner(0, 0, DCoordinate3(-1.0 + dx, 1.0 + dx, 0.0));
            patch.SetCorner(0, 1, DCoordinate3(1.0 + dx, 1.0 + dx, 0.0));
            patch.SetCorner(1, 0, DCoordinate3(-1.0 + dx, -1.0 + dx, 0.0));
            patch.SetCorner(1, 1, DCoordinate3(1.0 + dx, -1.0 + dx, 0.0));

            for (GLuint i = 0; i < 2; ++i)
            {
                for (GLuint j = 0; j < 2; ++j){
                    patch.SetUTangent(i, j, 0, 0, 1);
                    patch.SetVTangent(i, j, 0, 0, 1);
                    patch.SetTwistVector(i, j, 0, 0, 1);
                }
            }
//            patch.SetUTangent(0, 0, DCoordinate3(-1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, -1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, 0));
//            patch.SetUTangent(0, 1, DCoordinate3(-1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, -1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, 0));
//            patch.SetUTangent(1, 0, DCoordinate3(-1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, -1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, 0));
//            patch.SetUTangent(1, 1, DCoordinate3(-1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, -1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, 0));

//            patch.SetVTangent(0, 0, DCoordinate3(-1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, -1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, 0));
//            patch.SetVTangent(0, 1, DCoordinate3(-1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, -1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, 0));
//            patch.SetVTangent(1, 0, DCoordinate3(-1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, -1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, 0));
//            patch.SetVTangent(1, 1, DCoordinate3(-1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, -1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, 0));

//            patch.SetTwistVector(0, 0, DCoordinate3(-1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, -1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, 0));
//            patch.SetTwistVector(0, 1, DCoordinate3(-1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, -1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, 20));
//            patch.SetTwistVector(1, 0, DCoordinate3(-1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, -1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, 0));
//            patch.SetTwistVector(1, 1, DCoordinate3(-1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, -1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, -20));
        }

        patch.UpdateVertexBufferObjectsOfData();
        _attributes[attribute_count].image = patch.GenerateImage(u_div_point_count, v_div_point_count);
        TriangulatedMesh3 &image = *_attributes[attribute_count].image;
        image.UpdateVertexBufferObjects();
    }
    else 
    {
        _attributes.resize(1);
        _attributes[0].patch = new BicubicHermitePatch3();
        BicubicHermitePatch3 &patch = *_attributes[0].patch;
        patch.SetCorner(0, 0, DCoordinate3(-1, 1, 0)); //DCoordinate3(-1.0 + dx, 1.0 + dx, 0.0));
        patch.SetCorner(0, 1, DCoordinate3(1, 1, 0)); //DCoordinate3(1.0 + dx, 1.0 + dx, 0.0));
        patch.SetCorner(1, 0, DCoordinate3(-1, -1, 0)); //DCoordinate3(-1.0 + dx, -1.0 + dx, 0.0));
        patch.SetCorner(1, 1, DCoordinate3(1.0, -1.0, 0)); //DCoordinate3(1.0 + dx, -1.0 + dx, 0.0));

        patch.SetUTangent(0, 0, DCoordinate3(0, 0, 1)); //DCoordinate3(-1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, 1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, 0));
        patch.SetUTangent(0, 1, DCoordinate3(0, 0, 1)); //DCoordinate3(1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, 1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, 0));
        patch.SetUTangent(1, 0, DCoordinate3(0, 0, 1)); //DCoordinate3(-1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, -1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, 0));
        patch.SetUTangent(1, 1, DCoordinate3(0, 0, 1)); //DCoordinate3(1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, -1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, 0));

        patch.SetVTangent(0, 0, DCoordinate3(0, 0, 1)); //DCoordinate3(-1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, 1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, 0));
        patch.SetVTangent(0, 1, DCoordinate3(0, 0, 1)); //DCoordinate3(1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, 1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, 0));
        patch.SetVTangent(1, 0, DCoordinate3(0, 0, 1)); //DCoordinate3(-1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, -1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, 0));
        patch.SetVTangent(1, 1, DCoordinate3(0, 0, 1)); //DCoordinate3(1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, -1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, 0));

        patch.SetTwistVector(0, 0, DCoordinate3(0, 0, 1)); //DCoordinate3(-1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, 1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, 20));
        patch.SetTwistVector(0, 1, DCoordinate3(0, 0, 1)); //DCoordinate3(1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, 1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, 20));
        patch.SetTwistVector(1, 0, DCoordinate3(0, 0, 1)); //DCoordinate3(-1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, -1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, -20));
        patch.SetTwistVector(1, 1, DCoordinate3(0, 0, 1)); //DCoordinate3(1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, -1.0 + 2.0 * static_cast<double>(rand()) / RAND_MAX, -20));

        patch.UpdateVertexBufferObjectsOfData();
        _attributes[0].image = patch.GenerateImage(u_div_point_count, v_div_point_count);
        TriangulatedMesh3 &image = *_attributes[0].image;
        image.UpdateVertexBufferObjects();
    }

    dx += 2.25;
    return GL_TRUE;
}

GLboolean BicubicHermiteCompositeSurface3::DeleteExistingPatch(GLuint index)
{

    size_t attribute_count = _attributes.size();

    if (index >= attribute_count)
    {
        return GL_FALSE;
    }

    if (attribute_count)
    {
        for (GLuint i = 0; i < 8; ++i)
        {
            if (_attributes[index].neighbours[i])
            {
                // eloszor a szomszedokat
                _attributes[index].neighbours[i]->connection_type[_attributes[index].connection_type[i]] = 0;
                _attributes[index].neighbours[i]->neighbours[_attributes[index].connection_type[i]] = nullptr;

                _attributes[index].neighbours[i] = nullptr;
                _attributes[index].connection_type[i] = 0;
            }

        }

        size_t last = attribute_count - 1;

        if (index == last)
        {

            _attributes.pop_back();
        }
        else
        {
            swap(_attributes[index], _attributes[last]);

            _attributes[index].patch->DeleteVertexBufferObjectsOfData();
            _attributes[index].image->DeleteVertexBufferObjects();

            _attributes.pop_back();
        }

        return GL_TRUE;
    }
    else
    {
        return GL_FALSE;
    }
    return GL_TRUE;
}

GLboolean BicubicHermiteCompositeSurface3::ContinueExistingPatch(GLuint index, GLuint direction)
{
    if (index >= _attributes.size())
        return GL_FALSE;

    if (direction > 8)
        return GL_FALSE;

    if (_attributes[index].neighbours[direction])
        return GL_FALSE;

    BicubicHermitePatch3 *patch = new BicubicHermitePatch3();
    // A fo iranyok menten bovitunk
    if (direction < 4)
    {
        // i es ii a bal oldal pontjai
        GLuint i = _compass_right[direction].first, ii = _compass_right[direction].second,

        // j es jj a jobb oldal pontjai
        j = _compass_left[direction].first, jj = _compass_left[direction].second,

        // opi es opii a szembeni bal oldal pontja 
        opi = _compass_left[(direction + 2) % 4].first, opii = _compass_left[(direction + 2) % 4].second,

        // opj es opjj a szembeni jobb oldal pontja
        opj = _compass_right[(direction + 2) % 4].first, opjj = _compass_right[(direction + 2) % 4].second;


        cout << direction << ": " << i << ii << " " << j << jj << " es az ellentkezo: " << opi << opii << " " << opj << opjj << endl;

        patch->SetCorner(opi, opii, _attributes[index].patch->GetCorner(i, ii));
        patch->SetCorner(opj, opjj, _attributes[index].patch->GetCorner(j, jj));
        patch->SetCorner(i, ii, (
            _attributes[index].patch->GetCorner(i, ii) +
            _attributes[index].patch->GetCorner(i, ii) - 
            _attributes[index].patch->GetCorner(opi, opii)));
        patch->SetCorner(j, jj, (
            _attributes[index].patch->GetCorner(j, jj) + 
            _attributes[index].patch->GetCorner(j, jj) - 
            _attributes[index].patch->GetCorner(opj, opjj)));

        patch->SetUTangent(opi, opii, _attributes[index].patch->GetUTangent(i, ii));
        patch->SetUTangent(opj, opjj, _attributes[index].patch->GetUTangent(j, jj));
        patch->SetUTangent(i, ii, DCoordinate3());
        patch->SetUTangent(j, jj, DCoordinate3());

        patch->SetVTangent(opi, opii, _attributes[index].patch->GetVTangent(i, ii));
        patch->SetVTangent(opj, opjj, _attributes[index].patch->GetVTangent(j, jj));
        patch->SetVTangent(i, ii, DCoordinate3());
        patch->SetVTangent(j, jj, DCoordinate3());

        patch->SetTwistVector(opi, opii, _attributes[index].patch->GetTwistVector(i, ii));
        patch->SetTwistVector(opj, opjj, _attributes[index].patch->GetTwistVector(j, jj));
        patch->SetTwistVector(i, ii, DCoordinate3());
        patch->SetTwistVector(j, jj, DCoordinate3());

        InsertNewPatch(2, 100, 100, GL_STATIC_DRAW, *patch);

        _attributes[index].neighbours[direction] = &_attributes[_attributes.size() - 1];
        _attributes[_attributes.size() - 1].neighbours[(direction + 2) % 4] = &_attributes[index];

        _attributes[index].connection_type[direction] = (direction + 2) % 4;
        _attributes[_attributes.size() - 1].connection_type[(direction + 2) % 4] = direction;
    }
    // A kompozit iranyokban bovitunk
    // direction > 4 && direction < 8
    // 4 - NE, 5 - SE, 6 - SW, 7 - SE

    return GL_TRUE;
}

GLboolean BicubicHermiteCompositeSurface3::JoinExistingPatches(GLuint index_0, GLuint direction_0, GLuint index_1, GLuint direction_1)
{
    // God bless
    if (index_0 >= _attributes.size() || index_1 >= _attributes.size())
        return GL_FALSE;

    if (index_0 == index_1)
        return GL_FALSE;

    BicubicHermitePatch3* patch = new BicubicHermitePatch3();

    patch->SetCorner(_compass_left_join_origin[(direction_0+2)%4].first,_compass_left_join_origin[(direction_0+2)%4].second, _attributes[index_1].patch->GetCorner(_compass_left_join[direction_1].first,_compass_left_join[direction_1].second));
    patch->SetCorner(_compass_right_join_origin[(direction_0+2)%4].first,_compass_right_join_origin[(direction_0+2)%4].second, _attributes[index_1].patch->GetCorner(_compass_right_join[direction_1].first,_compass_right_join[direction_1].second));

    patch->SetUTangent(_compass_left_join_origin[(direction_0+2)%4].first,_compass_left_join_origin[(direction_0+2)%4].second, _attributes[index_1].patch->GetUTangent(_compass_left_join[direction_1].first,_compass_left_join[direction_1].second));
    patch->SetUTangent(_compass_right_join_origin[(direction_0+2)%4].first,_compass_right_join_origin[(direction_0+2)%4].second, _attributes[index_1].patch->GetUTangent(_compass_right_join[direction_1].first,_compass_right_join[direction_1].second));

    patch->SetVTangent(_compass_left_join_origin[(direction_0+2)%4].first,_compass_left_join_origin[(direction_0+2)%4].second, _attributes[index_1].patch->GetVTangent(_compass_left_join[direction_1].first,_compass_left_join[direction_1].second));
    patch->SetVTangent(_compass_right_join_origin[(direction_0+2)%4].first,_compass_right_join_origin[(direction_0+2)%4].second, _attributes[index_1].patch->GetVTangent(_compass_right_join[direction_1].first,_compass_right_join[direction_1].second));

    patch->SetTwistVector(_compass_left_join_origin[(direction_0+2)%4].first,_compass_left_join_origin[(direction_0+2)%4].second, _attributes[index_1].patch->GetTwistVector(_compass_left_join[direction_1].first,_compass_left_join[direction_1].second));
    patch->SetTwistVector(_compass_right_join_origin[(direction_0+2)%4].first,_compass_right_join_origin[(direction_0+2)%4].second, _attributes[index_1].patch->GetTwistVector(_compass_right_join[direction_1].first,_compass_right_join[direction_1].second));

//  std::vector<std::pair<GLuint, GLuint>> _compass_left_join_origin = { {1,0}, {0,0}, {0,0}, {0,1} };
//  std::vector<std::pair<GLuint, GLuint>> _compass_right_join_origin = { {1,1}, {1,0}, {0,1}, {1,1} };k
//  std::vector<std::pair<GLuint, GLuint>> _compass_left_join = { {0,0}, {0,1}, {1,0}, {0,0} };
//  std::vector<std::pair<GLuint, GLuint>> _compass_right_join = { {0,1}, {1,1}, {1,1}, {1,0} };

    patch->SetCorner(_compass_left_join_origin[direction_0].first,_compass_left_join_origin[direction_0].second, _attributes[index_0].patch->GetCorner(_compass_left_join[direction_0].first,_compass_left_join[direction_0].second));
    patch->SetCorner(_compass_right_join_origin[direction_0].first,_compass_right_join_origin[direction_0].second, _attributes[index_0].patch->GetCorner(_compass_right_join[direction_0].first,_compass_right_join[direction_0].second));

    patch->SetUTangent(_compass_left_join_origin[direction_0].first,_compass_left_join_origin[direction_0].second, _attributes[index_0].patch->GetUTangent(_compass_left_join[direction_0].first,_compass_left_join[direction_0].second));
    patch->SetUTangent(_compass_right_join_origin[direction_0].first,_compass_right_join_origin[direction_0].second, _attributes[index_0].patch->GetUTangent(_compass_right_join[direction_0].first,_compass_right_join[direction_0].second));

    patch->SetVTangent(_compass_left_join_origin[direction_0].first,_compass_left_join_origin[direction_0].second, _attributes[index_0].patch->GetVTangent(_compass_left_join[direction_0].first,_compass_left_join[direction_0].second));
    patch->SetVTangent(_compass_right_join_origin[direction_0].first,_compass_right_join_origin[direction_0].second, _attributes[index_0].patch->GetVTangent(_compass_right_join[direction_0].first,_compass_right_join[direction_0].second));

    patch->SetTwistVector(_compass_left_join_origin[direction_0].first,_compass_left_join_origin[direction_0].second, _attributes[index_0].patch->GetTwistVector(_compass_left_join[direction_0].first,_compass_left_join[direction_0].second));
    patch->SetTwistVector(_compass_right_join_origin[direction_0].first,_compass_right_join_origin[direction_0].second, _attributes[index_0].patch->GetTwistVector(_compass_right_join[direction_0].first,_compass_right_join[direction_0].second));

    _attributes[index_0].neighbours[direction_0] = &_attributes[_attributes.size() - 1];    // Az elso surfacehez a direction_0 iranyba lesz szomszed
    _attributes[index_0].connection_type[direction_0] = (direction_0+2)%4;  // Az elso surfacehez a kapcsolat a hozzafuggo neighbourhoz az ellentetes a north-al (vagyis south)
    _attributes[index_1].neighbours[direction_1] = &_attributes[_attributes.size() - 1];    // A masodik surfacenek direction_1 iranyba lesz szomszed
    _attributes[index_1].connection_type[direction_1] = direction_0;  // A masodik surfacehez a kapcsolat ellentetes mint ami van az elso surface-nek

    _attributes[_attributes.size() - 1].neighbours[(direction_0+2)%4] = &_attributes[index_0];  // Az uj patchnek lesz egy neighbourje northba (as always)
    _attributes[_attributes.size() - 1].connection_type[(direction_0+2)%4] = direction_0;   // Az uj patchnek a northba a kapcsolat direction_1-be lesz
    _attributes[_attributes.size() - 1].neighbours[direction_0] = &_attributes[index_1];  // Az uj patchnek lesz egy neighbourje (southba)
    _attributes[_attributes.size() - 1].connection_type[direction_0] = direction_1;   // Az uj patchnek a northba a kapcsolat direction_0-be lesz

    InsertNewPatch(2, 100, 100, GL_STATIC_DRAW, *patch);

    UpdatePatches(0);
    return GL_TRUE;
}

GLboolean BicubicHermiteCompositeSurface3::MergeExistingPatches(GLuint index_0, GLuint direction_0, GLuint index_1, GLuint direction_1)
{
    if (index_0 >= _attributes.size() || index_1 >= _attributes.size())
        return GL_FALSE;

    if (index_0 == index_1)
        return GL_FALSE;

    DCoordinate3 point1, point2, u1, u2, v1, v2, t1, t2;
    RotateMatrixNotClockwise(*_attributes[index_0].patch, direction_0);
    RotateMatrixNotClockwise(*_attributes[index_1].patch, (direction_1 + 2) % 4);

    point1 = _attributes[index_0].patch->GetCorner(0, 0) + _attributes[index_1].patch->GetCorner(1,0);
    point1 *= 0.5;

    point2 = _attributes[index_0].patch->GetCorner(0, 1) + _attributes[index_1].patch->GetCorner(1, 1);
    point2 *= 0.5;

    u1 = _attributes[index_0].patch->GetUTangent(0, 0) + _attributes[index_1].patch->GetUTangent(1, 0);
    u1 *= 0.5;

    u2 = _attributes[index_0].patch->GetUTangent(0, 1) + _attributes[index_1].patch->GetUTangent(1, 1);
    u2 *= 0.5;

    v1 = _attributes[index_0].patch->GetVTangent(0, 0) + _attributes[index_1].patch->GetVTangent(1, 0);
    v1 *= 0.5;

    v2 = _attributes[index_0].patch->GetVTangent(0, 1) + _attributes[index_1].patch->GetVTangent(1, 1);
    v2 *= 0.5;

    t1 = _attributes[index_0].patch->GetTwistVector(0, 0) + _attributes[index_1].patch->GetTwistVector(1, 0);
    t1 *= 0.5;

    t2 = _attributes[index_0].patch->GetTwistVector(0, 1) + _attributes[index_1].patch->GetTwistVector(1, 1);
    t2 *= 0.5;

    for (GLuint m = 0; m < _attributes.size(); m++)
    {
        for (GLuint k = 0; k < 4; k++)
        {
            if ( _attributes[m].patch->GetCorner(_compass_left[k].first, _compass_left[k].second)
                 == _attributes[index_0].patch->GetCorner(0,0)
                 && m!=index_0)
            {
                _attributes[m].patch->SetCorner(_compass_left[k].first, _compass_left[k].second, point1);
                _attributes[m].patch->SetVTangent(_compass_left[k].first, _compass_left[k].second, v1);
                _attributes[m].patch->SetUTangent(_compass_left[k].first, _compass_left[k].second, u1);
                _attributes[m].patch->SetTwistVector(_compass_left[k].first, _compass_left[k].second, t1);
            }
            else if ( _attributes[m].patch->GetCorner(_compass_right[k].first, _compass_right[k].second)
                      == _attributes[index_0].patch->GetCorner(0,0)
                      && m!=index_0)
            {
                _attributes[m].patch->SetCorner(_compass_right[k].first, _compass_right[k].second, point1);
                _attributes[m].patch->SetVTangent(_compass_right[k].first, _compass_right[k].second, v1);
                _attributes[m].patch->SetUTangent(_compass_right[k].first, _compass_right[k].second, u1);
                _attributes[m].patch->SetTwistVector(_compass_right[k].first, _compass_right[k].second, t1);
            }
        }
    }
    _attributes[index_0].patch->SetCorner(0, 0, point1);
    _attributes[index_0].patch->SetVTangent(0, 0, v1);
    _attributes[index_0].patch->SetUTangent(0, 0, u1);
    _attributes[index_0].patch->SetTwistVector(0, 0, t1);

    for (GLuint m = 0; m < _attributes.size(); m++)
    {
        for (GLuint k = 0; k < 4; k++)
        {
            if ( _attributes[m].patch->GetCorner(_compass_left[k].first, _compass_left[k].second)
                 == _attributes[index_1].patch->GetCorner(1,0)
                 && m!=index_1)

            {
                _attributes[m].patch->SetCorner(_compass_left[k].first, _compass_left[k].second, point1);
                _attributes[m].patch->SetVTangent(_compass_left[k].first, _compass_left[k].second, v1);
                _attributes[m].patch->SetUTangent(_compass_left[k].first, _compass_left[k].second, u1);
                _attributes[m].patch->SetTwistVector(_compass_left[k].first, _compass_left[k].second, t1);
            }
            else if ( _attributes[m].patch->GetCorner(_compass_right[k].first, _compass_right[k].second)
                      == _attributes[index_1].patch->GetCorner(1,0)
                      && m!=index_1)
            {
                _attributes[m].patch->SetCorner(_compass_right[k].first, _compass_right[k].second, point1);
                _attributes[m].patch->SetVTangent(_compass_right[k].first, _compass_right[k].second, v1);
                _attributes[m].patch->SetUTangent(_compass_right[k].first, _compass_right[k].second, u1);
                _attributes[m].patch->SetTwistVector(_compass_right[k].first, _compass_right[k].second, t1);
            }
        }
    }

    _attributes[index_1].patch->SetCorner(1, 0, point1);
    _attributes[index_1].patch->SetVTangent(1, 0, v1);
    _attributes[index_1].patch->SetUTangent(1, 0, u1);
    _attributes[index_1].patch->SetTwistVector(1, 0, t1);

    for (GLuint m = 0; m < _attributes.size(); m++)
    {
        for (GLuint k = 0; k < 4; k++)
        {
            if ( _attributes[m].patch->GetCorner(_compass_left[k].first, _compass_left[k].second)
                 == _attributes[index_0].patch->GetCorner(0,1)
                 && m!=index_0)

            {
                _attributes[m].patch->SetCorner(_compass_left[k].first, _compass_left[k].second, point2);
                _attributes[m].patch->SetVTangent(_compass_left[k].first, _compass_left[k].second, v2);
                _attributes[m].patch->SetUTangent(_compass_left[k].first, _compass_left[k].second, u2);
                _attributes[m].patch->SetTwistVector(_compass_left[k].first, _compass_left[k].second, t2);
            }
            else if ( _attributes[m].patch->GetCorner(_compass_right[k].first, _compass_right[k].second)
                      == _attributes[index_0].patch->GetCorner(0,1)
                      && m!=index_0)
            {
                _attributes[m].patch->SetCorner(_compass_right[k].first, _compass_right[k].second, point2);
                _attributes[m].patch->SetVTangent(_compass_right[k].first, _compass_right[k].second, v2);
                _attributes[m].patch->SetUTangent(_compass_right[k].first, _compass_right[k].second, u2);
                _attributes[m].patch->SetTwistVector(_compass_right[k].first, _compass_right[k].second, t2);
            }
        }
    }
    _attributes[index_0].patch->SetCorner(0, 1, point2);
    _attributes[index_0].patch->SetVTangent(0, 1, v2);
    _attributes[index_0].patch->SetUTangent(0, 1, u2);
    _attributes[index_0].patch->SetTwistVector(0, 1, t2);

    for (GLuint m = 0; m < _attributes.size(); m++)
    {
        for (GLuint k = 0; k < 4; k++)
        {
            if ( _attributes[m].patch->GetCorner(_compass_left[k].first, _compass_left[k].second)
                 == _attributes[index_1].patch->GetCorner(1,1)
                 && m!=index_1)

            {
                _attributes[m].patch->SetCorner(_compass_left[k].first, _compass_left[k].second, point2);
                _attributes[m].patch->SetVTangent(_compass_left[k].first, _compass_left[k].second, v2);
                _attributes[m].patch->SetUTangent(_compass_left[k].first, _compass_left[k].second, u2);
                _attributes[m].patch->SetTwistVector(_compass_left[k].first, _compass_left[k].second, t2);
            }
            else if ( _attributes[m].patch->GetCorner(_compass_right[k].first, _compass_right[k].second)
                      == _attributes[index_1].patch->GetCorner(1,1)
                      && m!=index_1)
            {
                _attributes[m].patch->SetCorner(_compass_right[k].first, _compass_right[k].second, point2);
                _attributes[m].patch->SetVTangent(_compass_right[k].first, _compass_right[k].second, v2);
                _attributes[m].patch->SetUTangent(_compass_right[k].first, _compass_right[k].second, u2);
                _attributes[m].patch->SetTwistVector(_compass_right[k].first, _compass_right[k].second, t2);
            }
        }
    }
    _attributes[index_1].patch->SetCorner(1, 1, point2);
    _attributes[index_1].patch->SetVTangent(1, 1, v2);
    _attributes[index_1].patch->SetUTangent(1, 1, u2);
    _attributes[index_1].patch->SetTwistVector(1, 1, t2);

    // Idaig

    RotateMatrixClockwise(*_attributes[index_0].patch, direction_0);
    RotateMatrixClockwise(*_attributes[index_1].patch, (direction_1 + 2) % 4);

    _attributes[index_1].neighbours[direction_1] = &_attributes[index_0];
    _attributes[index_0].neighbours[direction_0] = &_attributes[index_1];

    _attributes[index_1].connection_type[direction_1] = direction_0;
    _attributes[index_0].connection_type[direction_0] = direction_1;
    UpdatePatches(0);
    return GL_TRUE;
}


void BicubicHermiteCompositeSurface3::RenderAllFrames()
{
    for (GLuint i = 0; i < _attributes.size(); ++i)
    {
        BicubicHermitePatch3 &patch = *_attributes[i].patch;
        glBegin(GL_LINE_LOOP);
            glVertex3dv(&patch(0,0)[0]);
            glVertex3dv(&patch(0,1)[0]);
            glVertex3dv(&patch(1,1)[0]);
            glVertex3dv(&patch(1,0)[0]);
        glEnd();
    }
}

GLboolean BicubicHermiteCompositeSurface3::RenderSelectedNormals(GLuint index, GLdouble derivaive_scale)
{
    if (_attributes.size() <= index)
        return GL_FALSE;

    if (_attributes[index].image)
        _attributes[index].image->RenderNormals(derivaive_scale);

    return GL_TRUE;
}

GLboolean BicubicHermiteCompositeSurface3::RenderAllNormals(GLdouble derivaive_scale)
{
    GLuint n = _attributes.size();
    for (GLuint i = 0; i < n; ++i)
    {
        if (_attributes[i].image)
            _attributes[i].image->RenderNormals(derivaive_scale);
    }

    return GL_TRUE;
}

GLboolean BicubicHermiteCompositeSurface3::RenderAllData()
{
    GLuint n = _attributes.size();
    for (GLuint i = 0; i < n; ++i)
    {
        if (_attributes[i].patch)
            _attributes[i].patch->RenderData();
    }

    return GL_TRUE;
}

GLboolean BicubicHermiteCompositeSurface3::RenderSelectedData(GLuint index)
{
    if (_attributes.size() <= index)
        return GL_FALSE;

    if (_attributes[index].patch)
        _attributes[index].patch->RenderData();

    return GL_TRUE;
}

GLboolean BicubicHermiteCompositeSurface3::RenderAllPatches(GLuint order, GLenum render_mode) const
{
    if (order > 2)
        return GL_FALSE;

    GLuint n = _attributes.size();
    for (GLuint i = 0; i < n; ++i)
    {
        if (_attributes[i].image)
        {
            _attributes[i].image->Render();
        }
    }

    return GL_TRUE;
}

GLboolean BicubicHermiteCompositeSurface3::RenderSelectedPatch(GLuint index, GLuint order, GLenum render_mode) const
{
    if (_attributes[index].image)
    {
        _attributes[index].image->Render(render_mode);
    }

    return GL_TRUE;
}

RowMatrix<GenericCurve3*>* BicubicHermiteCompositeSurface3::GenerateUISO(GLuint index, GLuint iso_line_count,
                                        GLuint maximum_order_of_derivatives,
                                        GLuint div_point_count,
                                        GLenum usage_flag) const
{
    return _attributes[index].patch->GenerateUIsoparametricLines(iso_line_count, maximum_order_of_derivatives, div_point_count);
}

RowMatrix<GenericCurve3*>* BicubicHermiteCompositeSurface3::GenerateVISO(GLuint index, GLuint iso_line_count,
                                        GLuint maximum_order_of_derivatives,
                                        GLuint div_point_count,
                                        GLenum usage_flag) const
{
    return _attributes[index].patch->GenerateVIsoparametricLines(iso_line_count, maximum_order_of_derivatives, div_point_count);
}

DCoordinate3 BicubicHermiteCompositeSurface3::GetPointCoordinates(GLuint index, GLuint no){
    if (_attributes.size() <= index || no > 3)
        return DCoordinate3();

    GLuint i, j;
    if(no == 0) {
        i = 0;
        j = 0;
    } else if(no == 1) {
        i = 0;
        j = 1;
    } else if(no == 2) {
        j = 1;
        i = 1;
    } else {
        i = 1;
        j = 0;
    }
    return _attributes[index].patch->GetCorner(i, j);
}

DCoordinate3 BicubicHermiteCompositeSurface3::GetUCoordinates(GLuint index, GLuint no){
    if (_attributes.size() <= index || no > 3)
        return DCoordinate3();

    GLuint i, j;
    if(no == 0) {
        i = 0;
        j = 0;
    } else if(no == 1) {
        i = 0;
        j = 1;
    } else if(no == 2) {
        j = 1;
        i = 1;
    } else {
        i = 1;
        j = 0;
    }
    return _attributes[index].patch->GetUTangent(i, j);
}

DCoordinate3 BicubicHermiteCompositeSurface3::GetVCoordinates(GLuint index, GLuint no){
    if (_attributes.size() <= index || no > 3)
        return DCoordinate3();

    GLuint i, j;
    if(no == 0) {
        i = 0;
        j = 0;
    } else if(no == 1) {
        i = 0;
        j = 1;
    } else if(no == 2) {
        j = 1;
        i = 1;
    } else {
        i = 1;
        j = 0;
    }
    return _attributes[index].patch->GetVTangent(i, j);
}

DCoordinate3 BicubicHermiteCompositeSurface3::GetTCoordinates(GLuint index, GLuint no){
    if (_attributes.size() <= index || no > 3)
        return DCoordinate3();

    GLuint i, j;
    if(no == 0) {
        i = 0;
        j = 0;
    } else if(no == 1) {
        i = 0;
        j = 1;
    } else if(no == 2) {
        j = 1;
        i = 1;
    } else {
        i = 1;
        j = 0;
    }
    return _attributes[index].patch->GetTwistVector(i, j);
}

void BicubicHermiteCompositeSurface3::SetPointCoordinates(GLuint index, GLuint no, DCoordinate3 point){
    if (_attributes.size() <= index || no > 3)
        return;

    GLuint i, j;
    if(no == 0) {
        i = 0;
        j = 0;
    } else if(no == 1) {
        i = 0;
        j = 1;
    } else if(no == 2) {
        j = 1;
        i = 1;
    } else {
        i = 1;
        j = 0;
    }

//    _attributes[index].patch->SetCorner(i, j, point);

//    for (GLuint i = 0; i < 4; ++i)
//    {
//        if (_attributes[index].neighbours[i])
//        {
//            _attributes[index].neighbours[i]->patch->SetCorner(_compass_right[_attributes[index].connection_type[i]].first,
//                    _compass_right[_attributes[index].connection_type[i]].second,
//                    /*_attributes[index].patch->GetCorner(_compass_left[(_attributes[index].connection_type[i] + 2) % 4].first,
//                    _compass_left[(_attributes[index].connection_type[i] + 2) % 4].second));*/
//                    _attributes[index].patch->GetCorner(_compass_left[_attributes[index].neighbours[i]->connection_type[_attributes[index].connection_type[i]]].first,
//                                        _compass_left[_attributes[index].neighbours[i]->connection_type[_attributes[index].connection_type[i]]].second));

//            _attributes[index].neighbours[i]->patch->SetCorner(_compass_left[_attributes[index].connection_type[i]].first,
//                    _compass_left[_attributes[index].connection_type[i]].second,
////                    _attributes[index].patch->GetCorner(_compass_right[(_attributes[index].connection_type[i] + 2) % 4].first,
////                    _compass_right[(_attributes[index].connection_type[i] + 2) % 4].second));
//                    _attributes[index].patch->GetCorner(_compass_right[_attributes[index].neighbours[i]->connection_type[_attributes[index].connection_type[i]]].first,
//                                        _compass_right[_attributes[index].neighbours[i]->connection_type[_attributes[index].connection_type[i]]].second));

//        }
//    }

    for (GLuint m = 0; m < _attributes.size(); m++)
    {
        for (GLuint k = 0; k < 4; k++)
        {
            if ( _attributes[m].patch->GetCorner(_compass_left[k].first, _compass_left[k].second)
                 == _attributes[index].patch->GetCorner(i,j) /*&&
                 _attributes[m].patch->GetUTangent(_compass_left[k].first, _compass_left[k].second)
                 == _attributes[index].patch->GetUTangent(i,j) &&
                 _attributes[m].patch->GetVTangent(_compass_left[k].first, _compass_left[k].second)
                 == _attributes[index].patch->GetVTangent(i,j) &&
                 _attributes[m].patch->GetTwistVector(_compass_left[k].first, _compass_left[k].second)
                 == _attributes[index].patch->GetTwistVector(i,j)*/ &&
                 m!=index)

            {
                _attributes[m].patch->SetCorner(_compass_left[k].first, _compass_left[k].second, point);
            }
            else if ( _attributes[m].patch->GetCorner(_compass_right[k].first, _compass_right[k].second)
                      == _attributes[index].patch->GetCorner(i,j) /*&&
                      _attributes[m].patch->GetUTangent(_compass_right[k].first, _compass_right[k].second)
                      == _attributes[index].patch->GetUTangent(i,j) &&
                      _attributes[m].patch->GetVTangent(_compass_right[k].first, _compass_right[k].second)
                      == _attributes[index].patch->GetVTangent(i,j) &&
                      _attributes[m].patch->GetTwistVector(_compass_right[k].first, _compass_right[k].second)
                      == _attributes[index].patch->GetTwistVector(i,j)*/ &&
                      m!=index)
            {
                _attributes[m].patch->SetCorner(_compass_right[k].first, _compass_right[k].second, point);
            }
        }
    }

    _attributes[index].patch->SetCorner(i, j, point);
}

void BicubicHermiteCompositeSurface3::SetUCoordinates(GLuint index, GLuint no, DCoordinate3 point){
    if (_attributes.size() <= index || no > 3)
        return;

    GLuint i, j;
    if(no == 0) {
        i = 0;
        j = 0;
    } else if(no == 1) {
        i = 0;
        j = 1;
    } else if(no == 2) {
        j = 1;
        i = 1;
    } else {
        i = 1;
        j = 0;
    }

//    _attributes[index].patch->SetUTangent(i, j, point);

//    for (GLuint i = 0; i < 4; ++i)
//    {
//        if (_attributes[index].neighbours[i])
//        {

//            if ((i % 2 == 0 && _attributes[index].connection_type[i] % 2 == 1) || (i  % 2 == 1 && _attributes[index].connection_type[i] % 2 == 0))
//                continue;

//            _attributes[index].neighbours[i]->patch->SetUTangent(_compass_right[_attributes[index].connection_type[i]].first,
//                    _compass_right[_attributes[index].connection_type[i]].second,
//                    _attributes[index].patch->GetUTangent(_compass_left[_attributes[index].neighbours[i]->connection_type[_attributes[index].connection_type[i]]].first,
//                    _compass_left[_attributes[index].neighbours[i]->connection_type[_attributes[index].connection_type[i]]].second));

//            _attributes[index].neighbours[i]->patch->SetUTangent(_compass_left[_attributes[index].connection_type[i]].first,
//                    _compass_left[_attributes[index].connection_type[i]].second,
//                    _attributes[index].patch->GetUTangent(_compass_right[_attributes[index].neighbours[i]->connection_type[_attributes[index].connection_type[i]]].first,
//                    _compass_right[_attributes[index].neighbours[i]->connection_type[_attributes[index].connection_type[i]]].second));

//        }
//    }


    for (GLuint m = 0; m < _attributes.size(); m++)
    {
        for (GLuint k = 0; k < 4; k++)
        {
            if ( _attributes[m].patch->GetCorner(_compass_left[k].first, _compass_left[k].second)
                 == _attributes[index].patch->GetCorner(i,j) /*&&
                 _attributes[m].patch->GetUTangent(_compass_left[k].first, _compass_left[k].second)
                 == _attributes[index].patch->GetUTangent(i,j) &&
                 _attributes[m].patch->GetVTangent(_compass_left[k].first, _compass_left[k].second)
                 == _attributes[index].patch->GetVTangent(i,j) &&
                 _attributes[m].patch->GetTwistVector(_compass_left[k].first, _compass_left[k].second)
                 == _attributes[index].patch->GetTwistVector(i,j)*/ && m!=index)

            {
                _attributes[m].patch->SetUTangent(_compass_left[k].first, _compass_left[k].second, point);
            }
            else if ( _attributes[m].patch->GetCorner(_compass_right[k].first, _compass_right[k].second)
                      == _attributes[index].patch->GetCorner(i,j) /*&&
                      _attributes[m].patch->GetUTangent(_compass_right[k].first, _compass_right[k].second)
                      == _attributes[index].patch->GetUTangent(i,j) &&
                      _attributes[m].patch->GetVTangent(_compass_right[k].first, _compass_right[k].second)
                      == _attributes[index].patch->GetVTangent(i,j) &&
                      _attributes[m].patch->GetTwistVector(_compass_right[k].first, _compass_right[k].second)
                      == _attributes[index].patch->GetTwistVector(i,j)*/ && m!=index)
            {
                _attributes[m].patch->SetUTangent(_compass_right[k].first, _compass_right[k].second, point);
            }
        }
    }

    _attributes[index].patch->SetUTangent(i, j, point);
}

void BicubicHermiteCompositeSurface3::SetVCoordinates(GLuint index, GLuint no, DCoordinate3 point){
    if (_attributes.size() <= index || no > 3)
        return;

    GLuint i, j;
    if(no == 0) {
        i = 0;
        j = 0;
    } else if(no == 1) {
        i = 0;
        j = 1;
    } else if(no == 2) {
        j = 1;
        i = 1;
    } else {
        i = 1;
        j = 0;
    }
//    _attributes[index].patch->SetVTangent(i, j, point);

//    for (GLuint i = 0; i < 4; ++i)
//    {
//        if (_attributes[index].neighbours[i])
//        {
//            if ((i % 2 == 0 && _attributes[index].connection_type[i] % 2 == 1) || (i  % 2 == 1 && _attributes[index].connection_type[i] % 2 == 0))
//                continue;

//            _attributes[index].neighbours[i]->patch->SetVTangent(_compass_right[_attributes[index].connection_type[i]].first,
//                    _compass_right[_attributes[index].connection_type[i]].second,
//                    _attributes[index].patch->GetVTangent(_compass_left[_attributes[index].neighbours[i]->connection_type[_attributes[index].connection_type[i]]].first,
//                    _compass_left[_attributes[index].neighbours[i]->connection_type[_attributes[index].connection_type[i]]].second));

//            _attributes[index].neighbours[i]->patch->SetVTangent(_compass_left[_attributes[index].connection_type[i]].first,
//                    _compass_left[_attributes[index].connection_type[i]].second,
//                    _attributes[index].patch->GetVTangent(_compass_right[_attributes[index].neighbours[i]->connection_type[_attributes[index].connection_type[i]]].first,
//                    _compass_right[_attributes[index].neighbours[i]->connection_type[_attributes[index].connection_type[i]]].second));

//        }
//    }

    for (GLuint m = 0; m < _attributes.size(); m++)
    {
        for (GLuint k = 0; k < 4; k++)
        {
            if ( _attributes[m].patch->GetCorner(_compass_left[k].first, _compass_left[k].second)
                 == _attributes[index].patch->GetCorner(i,j) /*&&
                 _attributes[m].patch->GetUTangent(_compass_left[k].first, _compass_left[k].second)
                 == _attributes[index].patch->GetUTangent(i,j) &&
                 _attributes[m].patch->GetVTangent(_compass_left[k].first, _compass_left[k].second)
                 == _attributes[index].patch->GetVTangent(i,j) &&
                 _attributes[m].patch->GetTwistVector(_compass_left[k].first, _compass_left[k].second)
                 == _attributes[index].patch->GetTwistVector(i,j)*/ && m!=index)

            {
                _attributes[m].patch->SetVTangent(_compass_left[k].first, _compass_left[k].second, point);
            }
            else if ( _attributes[m].patch->GetCorner(_compass_right[k].first, _compass_right[k].second)
                      == _attributes[index].patch->GetCorner(i,j) /*&&
                      _attributes[m].patch->GetUTangent(_compass_right[k].first, _compass_right[k].second)
                      == _attributes[index].patch->GetUTangent(i,j) &&
                      _attributes[m].patch->GetVTangent(_compass_right[k].first, _compass_right[k].second)
                      == _attributes[index].patch->GetVTangent(i,j) &&
                      _attributes[m].patch->GetTwistVector(_compass_right[k].first, _compass_right[k].second)
                      == _attributes[index].patch->GetTwistVector(i,j)*/ && m!=index)
            {
                _attributes[m].patch->SetVTangent(_compass_right[k].first, _compass_right[k].second, point);
            }
        }
    }


    _attributes[index].patch->SetVTangent(i, j, point);
}

void BicubicHermiteCompositeSurface3::SetTCoordinates(GLuint index, GLuint no, DCoordinate3 point){
    if (_attributes.size() <= index || no > 3)
        return;

    GLuint i, j;
    if(no == 0) {
        i = 0;
        j = 0;
    } else if(no == 1) {
        i = 0;
        j = 1;
    } else if(no == 2) {
        j = 1;
        i = 1;
    } else {
        i = 1;
        j = 0;
    }
//    _attributes[index].patch->SetTwistVector(i, j, point);

//    for (GLuint i = 0; i < 4; ++i)
//    {
//        if (_attributes[index].neighbours[i])
//        {
//            if ((i % 2 == 0 && _attributes[index].connection_type[i] % 2 == 1) || (i % 2 == 1 && _attributes[index].connection_type[i] % 2 == 0))
//                continue;

//            _attributes[index].neighbours[i]->patch->SetTwistVector(_compass_right[_attributes[index].connection_type[i]].first,
//                    _compass_right[_attributes[index].connection_type[i]].second,
//                    _attributes[index].patch->GetTwistVector(_compass_left[_attributes[index].neighbours[i]->connection_type[_attributes[index].connection_type[i]]].first,
//                    _compass_left[_attributes[index].neighbours[i]->connection_type[_attributes[index].connection_type[i]]].second));

//            _attributes[index].neighbours[i]->patch->SetTwistVector(_compass_left[_attributes[index].connection_type[i]].first,
//                    _compass_left[_attributes[index].connection_type[i]].second,
//                    _attributes[index].patch->GetTwistVector(_compass_right[_attributes[index].neighbours[i]->connection_type[_attributes[index].connection_type[i]]].first,
//                    _compass_right[_attributes[index].neighbours[i]->connection_type[_attributes[index].connection_type[i]]].second));
//        }
//    }

    for (GLuint m = 0; m < _attributes.size(); m++)
    {
        for (GLuint k = 0; k < 4; k++)
        {
            if ( _attributes[m].patch->GetCorner(_compass_left[k].first, _compass_left[k].second)
                 == _attributes[index].patch->GetCorner(i,j) /*&&
                 _attributes[m].patch->GetUTangent(_compass_left[k].first, _compass_left[k].second)
                 == _attributes[index].patch->GetUTangent(i,j) &&
                 _attributes[m].patch->GetVTangent(_compass_left[k].first, _compass_left[k].second)
                 == _attributes[index].patch->GetVTangent(i,j) &&
                 _attributes[m].patch->GetTwistVector(_compass_left[k].first, _compass_left[k].second)
                 == _attributes[index].patch->GetTwistVector(i,j)*/ && m!=index)
            {
                _attributes[m].patch->SetTwistVector(_compass_left[k].first, _compass_left[k].second, point);

            }
            else if ( _attributes[m].patch->GetCorner(_compass_right[k].first, _compass_right[k].second)
                      == _attributes[index].patch->GetCorner(i,j) /*&&
                      _attributes[m].patch->GetUTangent(_compass_right[k].first, _compass_right[k].second)
                      == _attributes[index].patch->GetUTangent(i,j) &&
                      _attributes[m].patch->GetVTangent(_compass_right[k].first, _compass_right[k].second)
                      == _attributes[index].patch->GetVTangent(i,j) &&
                      _attributes[m].patch->GetTwistVector(_compass_right[k].first, _compass_right[k].second)
                      == _attributes[index].patch->GetTwistVector(i,j)*/ && m!=index)
            {
                _attributes[m].patch->SetTwistVector(_compass_right[k].first, _compass_right[k].second, point);
            }
        }
    }
        _attributes[index].patch->SetTwistVector(i, j, point);
}

void BicubicHermiteCompositeSurface3::UpdatePatches(GLuint index)
{
    for (GLuint i = 0; i < _attributes.size(); ++i)
    {
        _attributes[i].patch->DeleteVertexBufferObjectsOfData();
        _attributes[i].image->DeleteVertexBufferObjects();

        BicubicHermitePatch3 &patch = *_attributes[i].patch;
        patch.UpdateVertexBufferObjectsOfData();
        _attributes[i].image = patch.GenerateImage(50, 50);
        TriangulatedMesh3 &image = *_attributes[i].image;
        image.UpdateVertexBufferObjects();
    }
}

void BicubicHermiteCompositeSurface3::RotateMatrixClockwise(BicubicHermitePatch3 &patch, GLuint count)
{
    for(GLuint i = 0; i < count; i++) {
        DCoordinate3 tmp;
        tmp = patch.GetCorner(0, 0);
        patch.SetCorner(0, 0, patch.GetCorner(1, 0));
        patch.SetCorner(1, 0, patch.GetCorner(1, 1));
        patch.SetCorner(1, 1, patch.GetCorner(0, 1));
        patch.SetCorner(0, 1, tmp);

        tmp = patch.GetVTangent(0, 0);
        patch.SetVTangent(0, 0, patch.GetVTangent(1, 0));
        patch.SetVTangent(1, 0, patch.GetVTangent(1, 1));
        patch.SetVTangent(1, 1, patch.GetVTangent(0, 1));
        patch.SetVTangent(0, 1, tmp);

        tmp = patch.GetUTangent(0, 0);
        patch.SetUTangent(0, 0, patch.GetUTangent(1, 0));
        patch.SetUTangent(1, 0, patch.GetUTangent(1, 1));
        patch.SetUTangent(1, 1, patch.GetUTangent(0, 1));
        patch.SetUTangent(0, 1, tmp);

        tmp = patch.GetTwistVector(0, 0);
        patch.SetTwistVector(0, 0, patch.GetTwistVector(1, 0));
        patch.SetTwistVector(1, 0, patch.GetTwistVector(1, 1));
        patch.SetTwistVector(1, 1, patch.GetTwistVector(0, 1));
        patch.SetTwistVector(0, 1, tmp);
    }
}

void BicubicHermiteCompositeSurface3::RotateMatrixNotClockwise(BicubicHermitePatch3 &patch, GLuint count)
{
    for(GLuint i = 0; i < count; i++) {
        DCoordinate3 tmp;
        tmp = patch.GetCorner(0, 0);
        patch.SetCorner(0, 0, patch.GetCorner(0, 1));
        patch.SetCorner(0, 1, patch.GetCorner(1, 1));
        patch.SetCorner(1, 1, patch.GetCorner(1, 0));
        patch.SetCorner(1, 0, tmp);


        tmp = patch.GetVTangent(0, 0);
        patch.SetVTangent(0, 0, patch.GetVTangent(0, 1));
        patch.SetVTangent(0, 1, patch.GetVTangent(1, 1));
        patch.SetVTangent(1, 1, patch.GetVTangent(1, 0));
        patch.SetVTangent(1, 0, tmp);

        tmp = patch.GetUTangent(0, 0);
        patch.SetUTangent(0, 0, patch.GetUTangent(0, 1));
        patch.SetUTangent(0, 1, patch.GetUTangent(1, 1));
        patch.SetUTangent(1, 1, patch.GetUTangent(1, 0));
        patch.SetUTangent(1, 0, tmp);

        tmp = patch.GetTwistVector(0, 0);
        patch.SetTwistVector(0, 0, patch.GetTwistVector(0, 1));
        patch.SetTwistVector(0, 1, patch.GetTwistVector(1, 1));
        patch.SetTwistVector(1, 1, patch.GetTwistVector(1, 0));
        patch.SetTwistVector(1, 0, tmp);
    }
}

int BicubicHermiteCompositeSurface3::GetSize() {
    return _attributes.size();
}
