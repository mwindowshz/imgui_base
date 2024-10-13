# I added Hebrew support using this method
# adding glyphs that include the range for hebrew letters,
# then I added a fucntion to filp the text so I get RTL support
# here is code snippets

    self.impl = GlfwRenderer(self.window)

     # Load the Arial font from Windows fonts directory
    font_path = "C:\\Windows\\Fonts\\Arial.ttf"  # Use double backslashes
    font_size = 21.0  # Set the desired font size

    ranges = imgui.core.GlyphRanges([
            0x0020, 0x00FF,  # Basic Latin + Latin Supplement
            0x0590, 0x05FF,  # Hebrew
            0                # Null terminator
        ])      
    
    self.new_font = io.fonts.add_font_from_file_ttf(font_path, font_size,None,ranges)        

    self.impl.refresh_font_texture()


# a function to reverse the Hebrew or other RTL
def reverse_hebrew(text):
    # Split the text into words
    words = text.split()
    
    # Reverse each word and rejoin them
    reversed_words = [word[::-1] for word in words]
    
    # Reverse the order of the words and join them with spaces
    return ' '.join(reversed(reversed_words))
 during render
   imgui.text(revers_hebrew("זו דוגמא למשפט"))
This approch can be used in c++. but there need to take care of utf8

