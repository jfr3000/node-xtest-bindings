{
    "targets": [
        {
            "target_name": "NativeExtension",
            "sources": [ "myobject.cc"],
             "libraries": [
                "-lX11", "-lXtst"
            ],
            'cflags_cc+': ['-std=c++0x', '-L/usr/X11/lib', '-DXK_MISCELLANY'],
            "include_dirs" : [
 	 			"<!(node -e \"require('nan')\")"
			]
        }
    ],
}
