#pragma once

#include <glm/glm.hpp>

/*
    material structure to contain lighting values for different materials
*/

struct material {
    // lighting values
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;

    /*
        static instances of common materials
    */

    static material emerald;
    static material jade;
    static material obsidian;
    static material pearl;
    static material ruby;
    static material turquoise;
    static material brass;
    static material bronze;
    static material chrome;
    static material copper;
    static material gold;
    static material silver;
    static material black_plastic;
    static material cyan_plastic;
    static material green_plastic;
    static material red_plastic;
    static material white_plastic;
    static material yellow_plastic;
    static material black_rubber;
    static material cyan_rubber;
    static material green_rubber;
    static material red_rubber;
    static material white_rubber;
    static material yellow_rubber;
    static material wood;

    // function to mix two materials with a proportion
    static material mix(material m1, material m2, float mix = 0.5f);
};