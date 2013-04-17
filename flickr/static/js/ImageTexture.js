function ImageTexture(path, scene){
	
	var self = this;

	this.path = path;
	this.img = new Image();
	this.width  = 0;
	this.height = 0;
	this.plane = null;
	this.material = null;
	this.bLoaded = false;
	
	this.add = function(scene){
		scene.add(plane);
	}

	this.remove = function(scene){
		scene.remove(this.plane);
	}

	this.setScale = function(scale){
		self.plane.scale.x = scale;
		self.plane.scale.y = scale;
		self.plane.scale.z = scale;
	}

	this.img.onload = function(){
		self.width = self.img.width;
		self.height = self.img.height;
		self.material = new THREE.MeshLambertMaterial({
			map: THREE.ImageUtils.loadTexture(path)
		});
		self.plane = new THREE.Mesh(
			new THREE.PlaneGeometry(
				self.width,
				self.height,
				1,
				1
				),
			self.material);
		scene.add(self.plane);
		console.log("loaded texture - " + path);
		self.bLoaded = true;
	}
	this.img.src = path;
}