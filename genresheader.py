#!/usr/bin/env python3.0

import sys
import os
import glob

header = [ "#ifndef WXINCLUDE_IMAGES_H\n",
		   "#define WXINCLUDE_IMAGES_H\n",
		   "\n",
		   "#include <wx/wxprec.h>\n",
		   "#ifndef WX_PRECOMP\n",
		   "#include <wx/wx.h>\n",
		   "#endif\n",
		   "#include <wx/mstream.h>\n",
		   "\n",
		   "#define wxMEMORY_BITMAPEX(name, type) \\\n",
		   "		_wxConvertMemoryToBitmap(name, sizeof(name), type)\n",
		   "\n",
		   "inline wxBitmap _wxConvertMemoryToBitmap(const unsigned char* data, int length,\n",
		   "										 long type = wxBITMAP_TYPE_ANY) {\n",
		   "	wxMemoryInputStream stream(data, length);\n",
		   "	return wxBitmap(wxImage(stream, type, -1), -1);\n",
		   "}\n",
		   "\n" ]

footer = "#endif /* WXINCLUDE_IMAGES_H */\n"

with open(sys.argv[1], "w+") as f:
	f.writelines(header)

	for png in glob.iglob(os.path.join(sys.argv[2], "*.png")):
		name = os.path.splitext(os.path.basename(png))[0]
		f.write("static const unsigned char " + name + "[] = {\n")
		with open(png, "rb") as image:
			data = image.read()
			for byte in data:
				f.write(hex(byte))
				f.write(",")
		f.write("\n};\n\n")

	f.write(footer)