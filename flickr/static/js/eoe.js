var WIDTH = window.innerWidth,
	HEIGHT = window.innerHeight;

var VIEW_ANGLE = 45,
	ASPECT = WIDTH / HEIGHT,
	NEAR = 0.1,
	FAR = 10000;

var container;
var renderer = null;
var camera;
var scene; 

var sphereRadius = 50,
	sphereSegments = 16,
	sphereRings = 16;

var planeWidth = 240,
	planeHeight = 240,
	planeWSegments = 10,
	planeHSegments = 10;

var sphere;
var material;
var plane;

var pointLight;

var images = [];

var zTranslate = 0.0;
var it = null;

function init(){ 
	container = $('#container');
	renderer = new THREE.WebGLRenderer();
	renderer.autoClear = true;
	camera = new THREE.PerspectiveCamera(VIEW_ANGLE, ASPECT, NEAR, FAR);
	camera.position.z = 300;
	scene = new THREE.Scene();
	scene.add(camera);

	renderer.setSize(WIDTH, HEIGHT);
	container.append(renderer.domElement);

	material = new THREE.MeshLambertMaterial({color: 0xCC0000});

	/*
	material = new THREE.MeshLambertMaterial({
		map: THREE.ImageUtils.loadTexture(
			"static/img/dl/8610062699_c2c67c7fb1_m.jpg"
		)});
	*/

	sphere = new THREE.Mesh(
			 new THREE.SphereGeometry(
			 	sphereRadius,
			 	sphereSegments,
			 	sphereRings),
			 material);

	//scene.add(sphere);

	plane = new THREE.Mesh(
			new THREE.PlaneGeometry(
				planeWidth,
				planeHeight,
				planeWSegments,
				planeHSegments
			),
		material);

	//scene.add(plane);

	pointLight = new THREE.PointLight(0xFFFFFF);

	pointLight.position.x = 10;
	pointLight.position.y = 50;
	pointLight.position.z = 130;

	scene.add(pointLight);

	/*
	var textureImg = new Image();
	textureImg.onload = function(){
		console.log("image loaded");
		renderer.render(scene, camera);
	};
	textureImg.src = "static/img/dl/8610062699_c2c67c7fb1_m.jpg";
	*/

	it = new ImageTexture("static/img/dl/8610062699_c2c67c7fb1_m.jpg", scene);
	//renderer.render(scene, camera);
}

animate();

function animate(t){
	requestAnimationFrame(animate);
	draw(t);
}

function draw(t){
	//console.log(t);
	//console.log("drawing");
	//renderer.clear();
	if(renderer != null){
		renderer.render(scene, camera);
	}
	if(it != null){
		if(it.bLoaded){
			//console.log("translating z");
			//it.plane.translateZ(zTranslate);
			//zTranslate -= 1.0;
			//console.log(zTranslate);
			//if(zTranslate < -100.0){
			//	zTranslate = 0.0;
			//}
			it.setScale(0.1);
			it.plane.rotation.x = Math.sin(t / 1000.0);
			it.plane.rotation.y = Math.sin(t / 800.0);
		}
	}
}

(function() {
    var lastTime = 0;
    var vendors = ['ms', 'moz', 'webkit', 'o'];
    for(var x = 0; x < vendors.length && !window.requestAnimationFrame; ++x) {
        window.requestAnimationFrame = window[vendors[x]+'RequestAnimationFrame'];
        window.cancelAnimationFrame = window[vendors[x]+'CancelAnimationFrame']
                                   || window[vendors[x]+'CancelRequestAnimationFrame'];
    }
 
    if (!window.requestAnimationFrame)
        window.requestAnimationFrame = function(callback, element) {
            var currTime = new Date().getTime();
            var timeToCall = Math.max(0, 16 - (currTime - lastTime));
            var id = window.setTimeout(function() { callback(currTime + timeToCall); },
              timeToCall);
            lastTime = currTime + timeToCall;
            return id;
        };
 
    if (!window.cancelAnimationFrame)
        window.cancelAnimationFrame = function(id) {
            clearTimeout(id);
        };
}());