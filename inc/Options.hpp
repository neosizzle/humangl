#ifndef __OPTIONS__H__
#define __OPTIONS__H__

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

#include <map>
#include <string>
#include <vector>

/**
 * To debug, add this to render loop
*/
// get options
// std::cout
// << "bp " << options.get_selected_bp()
// << " color " << glm::to_string(options.get_colors()[options.get_selected_bp()])
// << " size " << options.get_sizes()[options.get_selected_bp()]
// << "\n";

/**
 * Options - represent the configuration for rendering
 * 
 * sizes <body_part, size> - size for each body part
 * colors <body_part, color> - color for each body part
 * body_parts - list of all body parts
 * color_options - list of all colors
 * selected_body_part - current selected body part by user
 * previous_key_pressed - previous key pressed by user
*/
class Options
{
private:
	std::map<std::string, float> sizes;
	std::map<std::string, glm::vec4> colors;
	std::vector<std::string> body_parts;
	std::vector<glm::vec4> color_options;
	std::string selected_body_part;
	int previous_key_pressed;

public:
	Options();
	~Options();

	std::map<std::string, float> get_sizes();
	std::map<std::string, glm::vec4> get_colors();
	std::string get_selected_bp();

	void handle_key(GLFWwindow *window);
};


#endif  //!__OPTIONS__H__