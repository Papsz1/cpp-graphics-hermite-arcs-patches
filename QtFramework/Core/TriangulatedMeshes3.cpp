#include <algorithm>
#include <cstring>
#include <fstream>
#include <limits>
#include <algorithm>
#include "TriangulatedMeshes3.h"

using namespace cagd;
using namespace std;

TriangulatedMesh3::TriangulatedMesh3(GLuint vertex_count, GLuint face_count, GLenum usage_flag):
    _usage_flag(usage_flag),
    _vbo_vertices(0), _vbo_normals(0), _vbo_tex_coordinates(0), _vbo_indices(0),
    _vertex(vertex_count), _normal(vertex_count), _tex(vertex_count),
    _face(face_count)
{
}

GLvoid TriangulatedMesh3::RenderNormals(GLdouble scale)
{
    glBegin(GL_LINES);
        for (GLuint i = 0; i < _vertex.size(); i++)
        {
            glVertex3dv(&_vertex[i][0]);
            DCoordinate3 sum = _vertex[i] + scale * _normal[i];
            glVertex3dv(&sum[0]);
        }
    glEnd();
}

TriangulatedMesh3::TriangulatedMesh3(const TriangulatedMesh3 &mesh):
        _usage_flag(mesh._usage_flag),
        _vbo_vertices(0), _vbo_normals(0), _vbo_tex_coordinates(0), _vbo_indices(0),
        _leftmost_vertex(mesh._leftmost_vertex), _rightmost_vertex(mesh._rightmost_vertex),
        _vertex(mesh._vertex),
        _normal(mesh._normal),
        _tex(mesh._tex),
        _face(mesh._face)
{
    if (mesh._vbo_vertices && mesh._vbo_normals && mesh._vbo_tex_coordinates && mesh._vbo_indices)
        UpdateVertexBufferObjects(mesh._usage_flag);
}

TriangulatedMesh3& TriangulatedMesh3::operator =(const TriangulatedMesh3& rhs)
{
    if (this != &rhs)
    {
        DeleteVertexBufferObjects();

        _usage_flag       = rhs._usage_flag;
        _leftmost_vertex  = rhs._leftmost_vertex;
        _rightmost_vertex = rhs._rightmost_vertex;
        _vertex		  = rhs._vertex;
        _normal		  = rhs._normal;
        _tex              = rhs._tex;
        _face             = rhs._face;

        if (rhs._vbo_vertices && rhs._vbo_normals && rhs._vbo_tex_coordinates && rhs._vbo_indices)
            UpdateVertexBufferObjects(_usage_flag);
    }

    return *this;
}

GLvoid TriangulatedMesh3::DeleteVertexBufferObjects()
{
    if (_vbo_vertices)
    {
        glDeleteBuffers(1, &_vbo_vertices);
        _vbo_vertices = 0;
    }

    if(_vbo_indices)
    {
        glDeleteBuffers(1, &_vbo_indices);
        _vbo_indices = 0;
    }

    if(_vbo_normals)
    {
        glDeleteBuffers(1, &_vbo_normals);
        _vbo_normals = 0;
    }

    if(_vbo_tex_coordinates)
    {
        glDeleteBuffers(1, &_vbo_tex_coordinates);
        _vbo_tex_coordinates = 0;
    }
}

GLboolean TriangulatedMesh3::Render(GLenum render_mode) const
{
    if (!_vbo_vertices || !_vbo_normals || !_vbo_tex_coordinates || !_vbo_indices)
        return GL_FALSE;

    if (render_mode != GL_TRIANGLES && render_mode != GL_POINTS)
        return GL_FALSE;

    // enable client states of vertex, normal and texture coordinate arrays
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

        // activate the VBO of texture coordinates
        glBindBuffer(GL_ARRAY_BUFFER, _vbo_tex_coordinates);
        // specify the location and data format of texture coordinates
        glTexCoordPointer(4, GL_FLOAT, 0, nullptr);

        // activate the VBO of normal vectors
        glBindBuffer(GL_ARRAY_BUFFER, _vbo_normals);
        // specify the location and data format of normal vectors
        glNormalPointer(GL_FLOAT, 0, nullptr);

        // activate the VBO of vertices
        glBindBuffer(GL_ARRAY_BUFFER, _vbo_vertices);
        // specify the location and data format of vertices
        glVertexPointer(3, GL_FLOAT, 0, nullptr);

        // activate the element array buffer for indexed vertices of triangular faces
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo_indices);

        // render primitives
        glDrawElements(render_mode, static_cast<GLsizei>(3 * _face.size()), GL_UNSIGNED_INT, nullptr);

    // disable individual client-side capabilities
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    // unbind any buffer object previously bound and restore client memory usage
    // for these buffer object targets
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return GL_TRUE;
}

GLboolean TriangulatedMesh3::UpdateVertexBufferObjects(GLenum usage_flag)
{
    if (usage_flag != GL_STREAM_DRAW  && usage_flag != GL_STREAM_READ  && usage_flag != GL_STREAM_COPY
     && usage_flag != GL_STATIC_DRAW  && usage_flag != GL_STATIC_READ  && usage_flag != GL_STATIC_COPY
     && usage_flag != GL_DYNAMIC_DRAW && usage_flag != GL_DYNAMIC_READ && usage_flag != GL_DYNAMIC_COPY)
        return GL_FALSE;

    // updating usage flag
    _usage_flag = usage_flag;

    // deleting old vertex buffer objects
    DeleteVertexBufferObjects();

    // creating vertex buffer objects of mesh vertices, unit normal vectors, texture coordinates,
    // and element indices
    glGenBuffers(1, &_vbo_vertices);

    if (!_vbo_vertices)
        return GL_FALSE;

    glGenBuffers(1, &_vbo_normals);

    if (!_vbo_normals)
    {
        glDeleteBuffers(1, &_vbo_vertices);
        _vbo_vertices = 0;
        return GL_FALSE;
    }

    glGenBuffers(1, &_vbo_tex_coordinates);
    if (!_vbo_tex_coordinates)
    {
        glDeleteBuffers(1, &_vbo_vertices);
        _vbo_vertices = 0;

        glDeleteBuffers(1, &_vbo_normals);
        _vbo_normals = 0;

        return GL_FALSE;
    }

    glGenBuffers(1, &_vbo_indices);
    if (!_vbo_indices)
    {
        glDeleteBuffers(1, &_vbo_vertices);
        _vbo_vertices = 0;

        glDeleteBuffers(1, &_vbo_normals);
        _vbo_normals = 0;

        glDeleteBuffers(1, &_vbo_tex_coordinates);
        _vbo_tex_coordinates = 0;

        return GL_FALSE;
    }

    // For efficiency reasons we convert all GLdouble coordinates
    // to GLfloat coordinates: we will use auxiliar pointers for
    // buffer data loading, by means of the functions glMapBuffer/glUnmapBuffer.

    // Notice that multiple buffers can be mapped simultaneously.

    size_t vertex_byte_size = 3 * _vertex.size() * sizeof(GLfloat);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo_vertices);
    glBufferData(GL_ARRAY_BUFFER, vertex_byte_size, nullptr, _usage_flag);

    GLfloat *vertex_coordinate = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo_normals);
    glBufferData(GL_ARRAY_BUFFER, vertex_byte_size, nullptr, _usage_flag);

    GLfloat *normal_coordinate = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    for (vector<DCoordinate3>::const_iterator
         vit = _vertex.begin(),
         nit = _normal.begin(); vit != _vertex.end(); ++vit, ++nit)
    {
        for (GLint component = 0; component < 3; ++component)
        {
            *vertex_coordinate = (GLfloat)(*vit)[component];
            ++vertex_coordinate;

            *normal_coordinate = (GLfloat)(*nit)[component];
            ++normal_coordinate;
        }
    }

    size_t tex_byte_size = 4 * _tex.size() * sizeof(GLfloat);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo_tex_coordinates);
    glBufferData(GL_ARRAY_BUFFER, tex_byte_size, nullptr, _usage_flag);
    GLfloat *tex_coordinate = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);

    memcpy(tex_coordinate, &_tex[0][0], tex_byte_size);

    size_t index_byte_size = 3 * _face.size() * sizeof(GLuint);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo_indices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_byte_size, nullptr, _usage_flag);
    GLuint *element = (GLuint*)glMapBuffer(GL_ELEMENT_ARRAY_BUFFER, GL_WRITE_ONLY);

    for (vector<TriangularFace>::const_iterator fit = _face.begin(); fit != _face.end(); ++fit)
    {
        for (GLint node = 0; node < 3; ++node)
        {
            *element = (*fit)[node];
            ++element;
        }
    }

    // unmap all VBOs
    glBindBuffer(GL_ARRAY_BUFFER, _vbo_vertices);
    if (!glUnmapBuffer(GL_ARRAY_BUFFER))
        return GL_FALSE;

    glBindBuffer(GL_ARRAY_BUFFER, _vbo_normals);
    if (!glUnmapBuffer(GL_ARRAY_BUFFER))
        return GL_FALSE;

    glBindBuffer(GL_ARRAY_BUFFER, _vbo_tex_coordinates);
    if (!glUnmapBuffer(GL_ARRAY_BUFFER))
        return GL_FALSE;

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo_indices);
    if (!glUnmapBuffer(GL_ELEMENT_ARRAY_BUFFER))
        return GL_FALSE;

    // unbind any buffer object previously bound and restore client memory usage
    // for these buffer object targets
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    return GL_TRUE;
}

GLboolean TriangulatedMesh3::LoadFromOFF(
        const string &file_name, GLboolean translate_and_scale_to_unit_cube)
{
    fstream f(file_name.c_str(), ios_base::in);

    if (!f || !f.good())
        return GL_FALSE;

    // loading the header
    string header;

    f >> header;

    if (header != "OFF")
        return GL_FALSE;

    // loading number of vertices, faces, and edges
    GLuint vertex_count, face_count, edge_count;

    f >> vertex_count >> face_count >> edge_count;

    // allocating memory for vertices, unit normal vectors, texture coordinates, and faces
    _vertex.resize(vertex_count);
    _normal.resize(vertex_count);
    _tex.resize(vertex_count);
    _face.resize(face_count);

    // initializing the leftmost and rightmost corners of the bounding box
    _leftmost_vertex.x() = _leftmost_vertex.y() = _leftmost_vertex.z() = numeric_limits<GLdouble>::max();
    _rightmost_vertex.x() = _rightmost_vertex.y() = _rightmost_vertex.z() = -numeric_limits<GLdouble>::max();

    // loading vertices and correcting the leftmost and rightmost corners of the bounding box
    for (vector<DCoordinate3>::iterator vit = _vertex.begin(); vit != _vertex.end(); ++vit)
    {
        f >> *vit;

        if (vit->x() < _leftmost_vertex.x())
            _leftmost_vertex.x() = vit->x();
        if (vit->y() < _leftmost_vertex.y())
            _leftmost_vertex.y() = vit->y();
        if (vit->z() < _leftmost_vertex.z())
            _leftmost_vertex.z() = vit->z();

        if (vit->x() > _rightmost_vertex.x())
            _rightmost_vertex.x() = vit->x();
        if (vit->y() > _rightmost_vertex.y())
            _rightmost_vertex.y() = vit->y();
        if (vit->z() > _rightmost_vertex.z())
            _rightmost_vertex.z() = vit->z();
    }

    // if we do not want to preserve the original positions and coordinates of vertices
    if (translate_and_scale_to_unit_cube)
    {
        GLdouble scale = 1.0 / max(_rightmost_vertex.x() - _leftmost_vertex.x(),
                                   max(_rightmost_vertex.y() - _leftmost_vertex.y(),
                                       _rightmost_vertex.z() - _leftmost_vertex.z()));

        DCoordinate3 middle(_leftmost_vertex);
        middle += _rightmost_vertex;
        middle *= 0.5;
        for (vector<DCoordinate3>::iterator vit = _vertex.begin(); vit != _vertex.end(); ++vit)
        {
            *vit -= middle;
            *vit *= scale;
        }
    }

    // loading faces
    for (vector<TriangularFace>::iterator fit = _face.begin(); fit != _face.end(); ++fit)
        f >> *fit;

    // calculating average unit normal vectors associated with vertices
    for (vector<TriangularFace>::const_iterator fit = _face.begin(); fit != _face.end(); ++fit)
    {
        DCoordinate3 n = _vertex[(*fit)[1]];
        n -= _vertex[(*fit)[0]];

        DCoordinate3 p = _vertex[(*fit)[2]];
        p -= _vertex[(*fit)[0]];

        n ^= p;

        for (GLint node = 0; node < 3; ++node)
            _normal[(*fit)[node]] += n;
    }

    for (vector<DCoordinate3>::iterator nit = _normal.begin(); nit != _normal.end(); ++nit)
        nit->normalize();

    f.close();

    return GL_TRUE;
}

GLboolean TriangulatedMesh3::SaveToOFF(const std::string& file_name) const
{
    fstream f(file_name.c_str(), ios_base::in);

    if (!f || !f.good())
        return GL_FALSE;

    // loading the header
    string header = "OFF";

    f << header << endl;

    f << VertexCount() << " " <<FaceCount() << " " <<  0 << endl; // NEM TUDOM MI AZ EDGE COUNT

    for (vector<DCoordinate3>::const_iterator vit = _vertex.begin(); vit != _vertex.end(); ++vit)
    {
        f << *vit << std::endl;
    }

    // loading faces
    for (vector<TriangularFace>::const_iterator fit = _face.begin(); fit != _face.end(); ++fit)
        f << *fit;

    f.close();
    return GL_TRUE;
}

GLfloat* TriangulatedMesh3::MapVertexBuffer(GLenum access_flag) const
{
    if (access_flag != GL_READ_ONLY && access_flag != GL_WRITE_ONLY && access_flag != GL_READ_WRITE)
        return (GLfloat*)0;

    glBindBuffer(GL_ARRAY_BUFFER, _vbo_vertices);
    GLfloat* result = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, access_flag);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return result;
}

GLvoid TriangulatedMesh3::UnmapVertexBuffer() const
{
    glBindBuffer(GL_ARRAY_BUFFER, _vbo_vertices);
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLfloat* TriangulatedMesh3::MapNormalBuffer(GLenum access_flag) const
{
    if (access_flag != GL_READ_ONLY && access_flag != GL_WRITE_ONLY && access_flag != GL_READ_WRITE)
        return (GLfloat*)0;

    glBindBuffer(GL_ARRAY_BUFFER, _vbo_normals);
    GLfloat* result = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, access_flag);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return result;
}
GLfloat* TriangulatedMesh3::MapTextureBuffer(GLenum access_flag) const
{
    if (access_flag != GL_READ_ONLY && access_flag != GL_WRITE_ONLY && access_flag != GL_READ_WRITE)
        return (GLfloat*)0;

    glBindBuffer(GL_ARRAY_BUFFER, _vbo_tex_coordinates);
    GLfloat* result = (GLfloat*)glMapBuffer(GL_ARRAY_BUFFER, access_flag);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    return result;
}

GLvoid TriangulatedMesh3::UnmapNormalBuffer() const
{
    glBindBuffer(GL_ARRAY_BUFFER, _vbo_normals);
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
GLvoid TriangulatedMesh3::UnmapTextureBuffer() const
{
    glBindBuffer(GL_ARRAY_BUFFER, _vbo_tex_coordinates);
    glUnmapBuffer(GL_ARRAY_BUFFER);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

size_t TriangulatedMesh3::VertexCount() const
{
//    size_t size = _vertex.size();
//    return size;
    return size_t(_face.size());

}
size_t TriangulatedMesh3::FaceCount() const
{
//    size_t size = _face.size();
//    return size;
    return size_t(_face.size());
}

TriangulatedMesh3::~TriangulatedMesh3()
{
    DeleteVertexBufferObjects();
}

// vertex count, face count
// list of vertices
// list of unit normal vectors
// list of texture coordinates
// list of faces
std::ostream& cagd::operator <<(std::ostream& lhs, const TriangulatedMesh3& rhs)
{
    GLuint vcount = rhs.VertexCount();
    GLuint fcount = rhs.FaceCount();
    lhs << vcount << " " << fcount << std::endl;

    for(std::vector<DCoordinate3>::const_iterator it = rhs._vertex.begin(); it != rhs._vertex.end(); it++)
    {
        lhs << &it << " ";
    }

    for(std::vector<DCoordinate3>::const_iterator it = rhs._normal.begin(); it != rhs._normal.end(); it++)
    {
        lhs << &it << " ";
    }

    for(std::vector<TCoordinate4>::const_iterator it = rhs._tex.begin(); it != rhs._tex.end(); it++)
    {
        lhs << &it << " ";
    }

    for(std::vector<TriangularFace>::const_iterator it = rhs._face.begin(); it != rhs._face.end(); it++)
    {
        lhs << &it << " ";
    }

    return lhs;
}

// input from stream: inverse of the ostream operator
std::istream& cagd::operator >>(std::istream& lhs, TriangulatedMesh3& rhs)
{
    rhs.DeleteVertexBufferObjects();

    GLuint vcount;
    GLuint fcount;
    lhs >> vcount >> fcount;

    lhs >> rhs._leftmost_vertex;
    lhs >> rhs._rightmost_vertex;

    rhs._vertex.resize(vcount);
    rhs._face.resize(fcount);
    rhs._normal.resize(vcount);
    rhs._tex.resize(vcount);

    for(std::vector<DCoordinate3>::iterator it = rhs._vertex.begin(); it != rhs._vertex.end(); it++)
    {
        lhs >> *it;
    }


    for(std::vector<DCoordinate3>::iterator it = rhs._normal.begin(); it != rhs._normal.end(); it++)
    {
        lhs >> *it;
    }

    for(std::vector<TCoordinate4>::iterator it = rhs._tex.begin(); it != rhs._tex.end(); it++)
    {
        lhs >> *it;
    }

    for(std::vector<TriangularFace>::iterator it = rhs._face.begin(); it != rhs._face.end(); it++)
    {
        lhs >> *it;
    }

    rhs.UpdateVertexBufferObjects();

    return lhs;
}

