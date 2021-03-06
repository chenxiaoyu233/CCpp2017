#include "Character.h"
#include <cmath>

float length(sf::Vector2f a){
	return sqrt(a.x*a.x + a.y*a.y);
}

void Character::set_null(){
	buff.clear();
}

void Character::be_impacted_from(Item *other){
	animation[cur_animation].set_position(physics.get_position());
	animation[cur_animation].be_affected(other -> get_cur_animation());
	if(other -> get_kind() == type_Room){//Room
		if(!animation[cur_animation].is_affect()){
			int tp = animation[cur_animation].stand_at(other -> get_cur_animation());
			int tagx = tp%3, tagy = tp/3;
			if(tagy != 1){
				sf::Vector2f tmp_mo = physics.get_motivation();
				if(tagy == 0){
					if(tmp_mo.y < 0) tmp_mo.y *= float(-1);
				}else if(tagy == 2){
					if(tmp_mo.y > 0) tmp_mo.y *= float(-1);
				}
				physics.set_motivation(tmp_mo);
			}
			if(tagx != 1){
				sf::Vector2f tmp_mo = physics.get_motivation();
				if(tagx == 0){
					if(tmp_mo.x < 0) tmp_mo.x *= float(-1);
				}else if(tagx == 2){
					if(tmp_mo.x > 0) tmp_mo.x *= float(-1);
				}
				physics.set_motivation(tmp_mo);
			}
		}
	}else if( other -> get_kind() == type_Bullet){ //Bullet
		if((animation[cur_animation].is_affect()) && ((item_kind == type_Enemy) || (item_kind == type_Enemy_1) || (item_kind == type_Enemy_2) || (item_kind == type_Enemy_3) || (item_kind == type_Enemy_4)) ){
				collision(physics, other -> physics);
				life.w[0] -= 5;
		}
	}else if(other -> get_kind() == type_Enemy_bullet){ //Enemy_bullet
		if(animation[cur_animation].is_affect() && item_kind == type_Player){
			collision(physics, other -> physics);
			if(!(cur_animation == 5 || cur_animation == 6 || cur_animation == 7)){//
				other -> dead();
				life.w[0] -= 100;
			}
		}
	}else if(other -> get_kind() == type_Enemy || other -> get_kind() == type_Enemy_1 || other -> get_kind() == type_Enemy_2 || other -> get_kind() == type_Enemy_3 || other -> get_kind() == type_Enemy_4){
		if(animation[cur_animation].is_affect() && (item_kind == type_Player)){
			collision(physics, other -> physics);
		}
		if(animation[cur_animation].is_affect() && (other -> get_kind() == type_Enemy_3 || other -> get_kind() == type_Enemy_4)){
			if(item_kind == type_Player){
				collision(physics, other -> physics);
				if(!((cur_animation == 5 || cur_animation == 6 || cur_animation == 7))){//
					life.w[0] -= 100;
				}
			}
		}
		if(animation[cur_animation].is_affect() && item_kind == type_Player){
			collision(physics, other -> physics);
			if(other -> get_kind() == type_Enemy || other -> get_kind() == type_Enemy_1 || other -> get_kind() == type_Enemy_2 || other -> get_kind() == type_Enemy_3 || other -> get_kind() == type_Enemy_4){
				if(cur_animation == 5 || cur_animation == 6){
					life.w[0] -= 50;
					other -> dead();
				}
			}
		}
	}

	//skill 效果
	/*if(item_kind == type_Player){
	  if(cur_animation == 5 || cur_animation == 6){
	  }
	  }*/
	/*sf::Vector2f pp = physics.get_position();
	if(pp.x < 50 || pp.x > 750 || pp.y < 50 || pp.y > 750) {
		cerr << "dead" << endl;
		dead();
		return;
	}*/
}

void Character::set_shot_direction(sf::Vector2f pos){
	shot_direction = pos - physics.get_position();
	if(length(shot_direction) != 0) shot_direction /= length(shot_direction);
}

Character::Character(int kind, string setting, sf::Vector2f pos, Director *world)
	:Item(kind,setting,pos,world){
		set_null();
	}

void Character::use_skill(int which){
	//if(!skill[which].is_ready()) return;
	//skill[which].use();
	cur_animation = which;
	animation[cur_animation].initlize();
	animation[cur_animation].set_play_flag(1);
	animation[cur_animation].set_sound_flag(1);
}


Character::~Character(){
	for(int i = 0; i < buff.size(); i++){
		delete buff[i];
	}
}

