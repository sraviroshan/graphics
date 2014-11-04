#ifndef _OPTIMUS_T_
#define _OPTIMUS_T_

class optimus_t{
public:
//Member variables
	GLuint texture[20];
	int rotation_angle; //angle for rotation about axis
	int body_rotation_x; //rotate body about x axis
	int body_rotation_y; //rotate body about x axis
	int body_rotation_z; //rotate body about x axis
	int back_weel_slab_rotation; //rotation of back weel slab bout x axis
	int solder_rotation_zl; //left solder rotation angle about z axis
	int solder_rotation_yl; //left solder rotation angle about y axis
	int solder_rotation_xl; // left solder rotation angle about x axis
	int elbows_rotation_l; //left elbows rotarion angle about z axis
	int solder_rotation_zr; // right solder rotation angle about z axis
	int solder_rotation_yr; // right solder rotation angle about y axis
	int solder_rotation_xr; // right solder rotation angle about x axis
	int elbows_rotation_r; //right elbows rotarion angle about z axis
	int waist_rotation; // rotation of waist about y axis
	int upper_body_rotation; //rotation of upper body about x axis
	int lower_leg_rotation_l; //rotation of left lower leg about x axis
	int lower_leg_rotation_r; //rotation of right lower leg about x axis
	int front_weel_slab_rotation; //rotarion of slab contain weel around x axis
	int uper_leg_rotation_xl; //rotation of uper left leg about x axis
	int uper_leg_rotation_zl; //rotation of uper left leg about z axis
	int uper_leg_rotation_xr; //rotation of uper right leg about x axis
	int uper_leg_rotation_zr; //rotation of uper right leg about z axis
	int hood_feet_rotation_xl1; //rotation of left whole feet about x axis
	int hood_feet_rotation_xl2; //rotation of left uper feet about x axis
	int hood_feet_rotation_xr1; //rotation of right whole feet about x axis
	int hood_feet_rotation_xr2; //rotation of right uper feet about x axis
	float throat_translate_y; //translation of throat along y axis
	int truck_ceiling_rotation; //rotation of truck ceilig about x axis
	int front_glass_rotation; //totation of fron glass bout x axis
	int side_gate_rotation; //side gate rotation about x axis
	int weel_rotation; //roatation of weel about z axis
	float forword_backword_movement_z; // translate whole body along z axis
	float forword_backword_movement_x; // translate whole body along x axis

	float vertical_movement; // vertical movement of transformer(independent)

	bool headlight_on;	// whether headlight on (decide which texture to load)

//Methods
	void init_structures(void);
	void load_textures();
	void hierarchi(); //main hierarchy builder

	void reset_transformer_config();
  	void reset_car_config();
  	void reset_view_angle();

  	void optimus_key_callback(int key, int scancode, int action, int mods);

	void configure_headlights(void);
	void set_lights();
	void headlight_left();
	void headlight_right();

	//structures parts
	void unit_cube(void);
	void torso(void);
	void uper_hand(void);
	void lower_hand(void);
	void waist(void);
	void uper_leg(void);
	void left_lower_leg(void);
	void right_lower_leg(void);
	void unit_weel(void);
	void front_weel_slab(void);
	void weel(void);
	void back_weel_slab(void);
	void hood_feet(void);
	void sphere(void);
	void sphere_layer(float, float, float);
	void hemisphere(void);
	void truck_ceiling(void);
	void front_glass(void);
	void hood_feet_left(void);
	void side_gate(void);

	//camera
	void set_camera_head(void);
	void set_camera_top(void);
};

#endif