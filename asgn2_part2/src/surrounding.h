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
    void unit_wall_without_texture();
	void back_wall(void);
	void front_wall(void);
	void left_wall(void);
	void right_wall(void);
	void top_wall(void);
	void floor_wall(void);

	void set_camera_wall_corner(void);
	void set_lights();
	
};

#endif
