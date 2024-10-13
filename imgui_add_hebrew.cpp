//thanks to @harelw
//for the support
//RTL strings handeling
// Function to determine the length of the UTF-8 character
size_t utf8_char_length(char c) {
	if ((c & 0x80) == 0x00) return 1; // 1-byte character
	if ((c & 0xE0) == 0xC0) return 2; // 2-byte character
	if ((c & 0xF0) == 0xE0) return 3; // 3-byte character
	if ((c & 0xF8) == 0xF0) return 4; // 4-byte character
	return 1; // Should not happen, treat as 1-byte character
}

// Function to reverse a UTF-8 string
std::string reverse_utf8(const std::string_view input) {
	std::vector<std::string_view> characters;
	size_t i = 0;

	while (i < input.size()) {
		size_t char_len = utf8_char_length(input[i]);
		characters.push_back(input.substr(i, char_len));
		i += char_len;
	}

	// Reverse the order of the characters and concatenate them using ranges and views
	auto reversed_view = characters | std::views::reverse | std::views::join;

	return std::string(reversed_view.begin(), reversed_view.end());
}

// Load Fonts
static const ImWchar ranges[] =
{
	0x0020, 0x00FF, // Basic Latin + Latin Supplement
	0x0590, 0x05FF, // Greek and Coptic
	0,
};
ImFont* font = io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\arial.ttf", 22.0f, nullptr, &ranges[0]);


in render loop
use push_font
and pop_font

ImGuiIO& io = ImGui::GetIO();
static ImFont* my_font = io.Fonts->Fonts[1];
ImGui::PushFont(my_font);
ImGui::Text(reverse_utf8("some example"))
Imgui::Text("זו רק דוגמא")
ImGui::PopFont()
