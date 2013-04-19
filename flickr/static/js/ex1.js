var camera, scene, renderer;
var windowScale;
var cameraControls;
var clock = new THREE.Clock();

function drawGoldCube(){
	var cube;
	var cubeSizeLength = 100;
	var goldColor = '#FFDF00';
	var showFrame = true;
	var wireMaterial = new THREE.MeshBasicMaterial({color: goldColor, wireFrame: showFrame});
	var cubeGeometry = new THREE.CubeGeometry(cubeSizeLength, cubeSizeLength, cubeSizeLength);
	var cube = new THREE.Mesh(cubeGeometry, wireMaterial);
	cube.position.x = 0;
	cube.position.y = 0;
	cube.position.z = 0;
	scene.add(cube);
}

function init(){
	var canvasWidth = window.innerWidth - 8;
	var canvasHeight = window.innerHeight - 16;
	var canvasRatio = canvasWidth / canvasHeight;

	scene = new THREE.Scene();
	scene.fog = new THREE.Fog(0x808080, 2000, 4000);

	scene.add(new THREE.AmbientLight(0x222222));

	renderer = new THREE.WebGLRenderer({antialias: true});
	renderer.gammaInput = true;
	renderer.gammaOutput = true;
	renderer.setSize(canvasWidth, canvasHeight);
	renderer.setClearColor(scene.fog.color, 1);

	var container = $('#container');
	container.append(renderer.domElement);

	camera = new THREE.PerspectiveCamera(45, canvasRatio, 1, 4000);	
	camera.position.set(-200, 200, -150);

	//cameraControls = new THREE.OrbitAndPanControls(camera, renderer.domElement);
	//cameraControls.target.set(0,0,0);

	scene.add(camera);

	//Coordinates.drawGrid({size: 1000, scale:0.01});
	//Coordinates.drawGrid({size: 1000, scale:0.01, orientation:'y'});
	//Coordinates.drawGrid({size: 1000, scale:0.01, orientation:'z'});
}


function animate(){
	requestAnimationFrame(animate);
	render();
}

function render(){
	var delta = clock.getDelta();
	//cameraControls.update(delta);
	renderer.render(scene, camera);
}

init();
drawGoldCube();
animate();