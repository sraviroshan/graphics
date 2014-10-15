#ifndef _SURROUNDING_T_
#define _SURROUNDING_T_

class surrounding_t{
public:
	GLuint texture[10];
	//method
	void init_surrounding(void);
	void surround_all();//construct surrending
	void load_textures();


	//structure
	void back_wall(void);
	void front_wall(void);
	void left_wall(void);
	void right_wall(void);
	void top_wall(void);
	void floor_wall(void);
};

#endif