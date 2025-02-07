#pragma once

class player {
private:
	int	  _id;
	float _x;
	float _y;
	float _speed = 200.f;

public:

	player(int id);

	void update(float delta_time);
	void update_movement(float delta_time);
	void upload_render_data() const;

	float get_x() const;
	float get_y() const;
};