cmd_Release/cloudcv.node := ln -f "Release/obj.target/cloudcv.node" "Release/cloudcv.node" 2>/dev/null || (rm -rf "Release/cloudcv.node" && cp -af "Release/obj.target/cloudcv.node" "Release/cloudcv.node")
