#include "imgLoader.h"
#include "picopng.h"
#include "IOmanager.h"
#include "stdio.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include "lodepng.h"

imgLoader::imgLoader()
{
    //ctor
}
texture imgLoader::loadPNG(const std::string &path){
    texture tex={};
    //std::vector<unsigned char> in;
    std::vector<unsigned char> outpic;
    unsigned width,height;
	/*
    if(!IOmanager::readFileToBuffer(path,in)){
        std::cout<<"4\n"<<std::endl;
        glfwTerminate();
    }*/
    int error = lodepng::decode(outpic,width,height,path.c_str());
    if(error){
		std::cout << "decondPNG failed with" << error << std::endl;
        glfwTerminate();
        return tex;
    }
    glGenTextures(1,&(tex.id));
    glBindTexture(GL_TEXTURE_2D,tex.id);

    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,width,height,0,GL_RGBA,GL_UNSIGNED_BYTE,&(outpic[0]));
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glGenerateMipmap(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,0);
    tex.width = width;
    tex.height = height;
    return tex;
}
