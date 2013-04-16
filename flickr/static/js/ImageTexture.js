function ImageTexture(path, scene){
	var path = path;
	var img = new Image();
	var width  = 0;
	var hwight = 0;
	var plane = null;
	var material = null;
	var bLoaded = false;
	this.add = function(scene){
		scene.add(plane);
	}
	this.remove = function(scene){
		scene.remove(this.plane);
	}
	img.onload = function(){
		width = img.width;
		height = img.height;
		material = new THREE.MeshLambertMaterial({
			map: THREE.ImageUtils.loadTexture(path)
		});
		plane = new THREE.Mesh(
			new THREE.PlaneGeometry(
				width,
				height,
				1,
				1
				),
			material);
		scene.add(plane);
		console.log("loaded texture - " + path);
		bLoaded = true;
	}
	img.src = path;
}