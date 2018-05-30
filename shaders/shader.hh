#pragma once

#include <exception>

#include "gl/includes.hh"

namespace shaders {

class Shader {
 public:
    enum class Type { VERTEX = 1, FRAGMENT = 2, GEOMETRY = 3 };

    Shader(const Type type, const char *source) : type{type}, source_{source} {
        Glenum gl_shader_type;
        switch (type) {
            case VERTEX:
                gl_shader_type = GL_VERTEX_SHADER;
                break;
            case FRAGMENT:
                gl_shader_type = GL_FRAGMENT_SHADER;
                break;
            case GEOMETRY:
                gl_shader_type = GL_GEOMETRY_SHADER;
                break;
        }

        id_ = glCreateShader(gl_shader_type);
        glShaderSource(id_, 1, source_, nullptr);
        glCompileShader(id_);

        int success;
        char info_log[512];
        glGetShaderiv(id_, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(id_, 512, nullptr, info_log);
            // TODO
            std::cerr << "ERROR compiling shader: " << info_log << std::endl;
            assert(false);
        }
    }

    const Type type;
    uint id() const { return id_; }

 private:
    const char source_[];
    uint id_ = 0;
};

class ShaderProgram {
 public:
 private:
};
}  // namespace shaders
