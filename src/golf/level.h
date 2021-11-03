#ifndef _GOLF_LEVEL_H
#define _GOLF_LEVEL_H

#include "3rd_party/vec/vec.h"
#include "golf/data.h"
#include "golf/file.h"
#include "golf/maths.h"

typedef struct golf_terrain_entity_vertex {
    vec3 position;
    vec3 normal;
    vec2 texturecoord;
} golf_terrain_entity_vertex_t;
typedef vec_t(golf_terrain_entity_vertex_t) vec_golf_terrain_entity_vertex_t;

typedef struct golf_terrain_entity_face {
    int num_vertices;
    golf_terrain_entity_vertex_t vertices[4];
} golf_terrain_entity_face_t;
typedef vec_t(golf_terrain_entity_face_t) vec_golf_terrain_entity_face_t;

typedef struct golf_terrain_entity {
    vec3 position;
    vec3 scale;
    quat orientation;
    vec_golf_terrain_entity_face_t faces;
} golf_terrain_entity_t;

typedef struct golf_model_entity {
    vec3 position;
    vec3 scale;
    quat orientation;
    char model_path[GOLF_FILE_MAX_PATH];
    golf_data_model_t *model;
    float bounds[6];
} golf_model_entity_t;
typedef vec_t(golf_model_entity_t*) vec_golf_model_entity_ptr_t;
mat4 golf_model_entity_get_model_mat(golf_model_entity_t *entity);

typedef enum golf_entity_type {
    TERRAIN_ENTITY,
    MODEL_ENTITY,
} golf_entity_type_t;

typedef struct golf_entity {
    golf_entity_type_t type;
    union {
        golf_model_entity_t model;
        golf_terrain_entity_t terrain;
    };
} golf_entity_t;
typedef vec_t(golf_entity_t) vec_golf_entity_t;

typedef struct golf_level {
    vec_golf_entity_t entities;
} golf_level_t;

bool golf_level_save(golf_level_t *level, const char *path);
bool golf_level_load(golf_level_t *level, const char *path, char *data, int data_len);
bool golf_level_unload(golf_level_t *level);

#endif
