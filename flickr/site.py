import redis
import web
import json

render = web.template.render('templates/')

urls = (
	'/', 'Index',
	'/viewimgs', 'ViewImgs',
	'/getimgs', "GetImgs",
)

r_s = redis.Redis()
app = web.application(urls, globals())

class Index:

	def GET(self):
		return render.index()

class ViewImgs:

	def GET(self):
		urls = []
		photo_keys = r_s.keys('photo:*')
		for i in photo_keys:
			urls.append(r_s.hget(i, 'url'))
		return render.view(urls)

class GetImgs:

	def GET(self):
		urls = []
		photo_keys = r_s.keys('photo:*')
		for i in photo_keys:
			url = r_s.hget(i, 'url')
			if url is not None:
				urls.append(url)
		web.header('Content-Type', 'application/json');
		return json.dumps(urls)

def main():
	app.run()

if __name__ == "__main__":
	main()