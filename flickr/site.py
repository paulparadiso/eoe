import redis
import web

render = web.template.render('templates/')

urls = (
	'/', 'Index',
)

r_s = redis.Redis(
)
app = web.application(urls, globals())

class Index:

	def GET(self):
		return render.index()

def main():
	app.run()

if __name__ == "__main__":
	main()