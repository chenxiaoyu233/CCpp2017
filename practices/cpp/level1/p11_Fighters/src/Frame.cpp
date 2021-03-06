#include "Animation.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
using namespace std;

Frame::Frame(){
	memset(x,0,sizeof(x));
	memset(y,0,sizeof(y));
	core_position.x = core_position.y = 0;
	del_position.x = del_position.y = 0;
	impact_flag = hurt_flag = 0;
}

Frame::Frame( string image_file_name, string image_info_file_name ){
	memset(x,0,sizeof(x));
	memset(y,0,sizeof(y));
	core_position.x = core_position.y = 0;
	del_position.x = del_position.y = 0;
	impact_flag = hurt_flag = 0;
	set_image(image_file_name);
	set_image_info(image_info_file_name);
}

void Frame::update_draw_position(){
	x[0] = core_position.x - del_position.x;
	x[1] = x[0] + image.getSize().x;//length.x;
	y[0] = core_position.y - del_position.y;
	y[1] = y[0] + image.getSize().y;//length.y;
	sprite.setPosition(core_position - del_position);
}

void Frame::display(sf::RenderWindow *win){
	win -> draw(sprite);
}

void Frame::set_image(string image_file_name){
	if(!image.loadFromFile(image_file_name)){
		cerr << "fail to open the image in: " << image_file_name << endl;
		exit(0);
	}
	if(!texture.loadFromImage(image)){
		cerr << "fail to open the image obj" << endl;
		exit(0);
	}
	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(0,0,image.getSize().x, image.getSize().y));
	//length = image.getSize();
	length.x = image.getSize().x;
	length.y = image.getSize().y;
}

void Frame::set_length(sf::Vector2f len){
	length = len;
}

void Frame::set_image_info(string image_info_file_name){
	char tmp[1005];
	FILE *in = fopen(image_info_file_name.c_str(), "r");
	if(in == NULL){
		cerr << "fail to open in Frame.cpp " << endl;
		cerr << image_info_file_name << endl;
		exit(0);
	}
	fscanf(in," %f%f", &del_position.x,&del_position.y);
	//del_position.y = image.getSize().y;
	fclose(in);
}

void Frame::set_core_position(sf::Vector2f position){
	//cerr << position.x << " " << position.y << endl;
	core_position = position;
	update_draw_position();
}

int Frame::is_in(const sf::Vector2f &point){
	return (x[0] <= point.x && x[1] >= point.x) && 
		(y[0] <= point.y && y[1] >= point.y);
}

int Frame::is_in(Frame *other){
	int tag1 = 0, tag2 = 0;
	if(core_position.x < other -> x[0]){
		tag1 = 0;
	}else if(core_position.x >= other -> x[0] && core_position.x <= other -> x[1]){
		tag1 = 1;
	}else if(core_position.x > other -> x[1]){
		tag1 = 2;
	}

	if(core_position.y < other -> y[0]){
		tag2 = 0;
	}else if(core_position.y >= other -> y[0] && core_position.y <= other -> y[1]){
		tag2 = 1;
	}else if(core_position.y > other -> y[1]){
		tag2 = 2;
	}

	return tag2*3 + tag1;
}

void Frame::set_scale(sf::Vector2f scale){
	sprite.setScale(scale);
}
