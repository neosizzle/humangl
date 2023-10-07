#include "Options.hpp"

#include <algorithm>

template <typename T>
int getIndex(const std::vector<T>& v, const T& value)
{
    auto it = std::find(v.begin(), v.end(), value);

    if (it != v.end())
    {
        return std::distance(v.begin(), it);
    }
    
    return -1;
}

Options::Options(){
	this->body_parts.push_back("hip_joint");
	this->body_parts.push_back("ul_leg");
	this->body_parts.push_back("ll_leg");
	this->body_parts.push_back("ur_leg");
	this->body_parts.push_back("lr_leg");
	this->body_parts.push_back("chest");
	this->body_parts.push_back("ul_arm");
	this->body_parts.push_back("ll_arm");
	this->body_parts.push_back("ur_arm");
	this->body_parts.push_back("lr_arm");
	this->body_parts.push_back("neck");
	this->body_parts.push_back("head");

	this->selected_body_part = "hip_joint";

	this->color_options.push_back(Vector(4, {0.0f, 0.0f, 1.0f, 1.0f}));
	this->color_options.push_back(Vector(4, {1.0f, 0.0f, 0.0f, 1.0f}));
	this->color_options.push_back(Vector(4, {0.0f, 1.0f, 0.0f, 1.0f}));

	for (std::string body_part : this->body_parts) {
       this->sizes.insert(std::make_pair(body_part, 1.0f));
	   this->colors.insert(std::make_pair(body_part, this->color_options[0]));
   }
}

Options::~Options(){}

std::map<std::string, float> Options::get_sizes(){return this->sizes;}

std::map<std::string, Vector> Options::get_colors(){return this->colors;}

std::string Options::get_selected_bp(){return this->selected_body_part;}

void Options::handle_key(GLFWwindow *window)
{
	// log key
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		this->previous_key_pressed = GLFW_KEY_LEFT;
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		this->previous_key_pressed = GLFW_KEY_RIGHT;
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		this->previous_key_pressed = GLFW_KEY_UP;
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		this->previous_key_pressed = GLFW_KEY_DOWN;
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS)
	{
		this->previous_key_pressed = GLFW_KEY_EQUAL;
		return;
	}
	if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS)
	{
		this->previous_key_pressed = GLFW_KEY_MINUS;
		return;
	}

	// switch between body parts
	const int curr_bp_idx = getIndex(this->body_parts, this->selected_body_part);
	if (this->previous_key_pressed == GLFW_KEY_LEFT && glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_RELEASE)
	{
		if (curr_bp_idx == 0)
			this->selected_body_part = this->body_parts[this->body_parts.size() - 1];
		else
			this->selected_body_part = this->body_parts[curr_bp_idx - 1];

		// reset key
		this->previous_key_pressed = 0;
	}
	if (this->previous_key_pressed == GLFW_KEY_RIGHT && glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_RELEASE)
	{
		if (curr_bp_idx == this->body_parts.size() - 1)
			this->selected_body_part = this->body_parts[0];
		else
			this->selected_body_part = this->body_parts[curr_bp_idx + 1];

		// reset key
		this->previous_key_pressed = 0;
	}


	// increase / decrease color on current body part
	const int curr_color_idx = getIndex(this->color_options, this->colors[this->selected_body_part]);
	if (this->previous_key_pressed == GLFW_KEY_UP && glfwGetKey(window, GLFW_KEY_UP) == GLFW_RELEASE)
	{
		if (curr_color_idx == 0)
			this->colors[this->selected_body_part] = this->color_options[this->color_options.size() - 1];
		else
			this->colors[this->selected_body_part] = this->color_options[curr_color_idx - 1];

		// reset key
		this->previous_key_pressed = 0;
	}
	if (this->previous_key_pressed == GLFW_KEY_DOWN && glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_RELEASE)
	{
		if (curr_color_idx == this->color_options.size() - 1)
			this->colors[this->selected_body_part] = this->color_options[0];
		else
			this->colors[this->selected_body_part] = this->color_options[curr_color_idx + 1];

		// reset key
		this->previous_key_pressed = 0;
	}


	// increase / decrease scale on current body part 
	const int curr_size = this->sizes[selected_body_part];
	if (this->previous_key_pressed == GLFW_KEY_EQUAL && glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_RELEASE)
	{
		if (curr_color_idx < 3.0f )
			this->sizes[selected_body_part] += 0.1;

		// reset key
		this->previous_key_pressed = 0;
	}
	if (this->previous_key_pressed == GLFW_KEY_MINUS && glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_RELEASE)
	{
		if (curr_color_idx > 0.5f )
			this->sizes[selected_body_part] -= 0.1;

		// reset key
		this->previous_key_pressed = 0;
	}


}