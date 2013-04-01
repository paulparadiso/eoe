from flickr import FlickrAPI
import redis

api_key = '5c28f35a444332cbb9e19d15bbbffdf5'
api_secret = 'a631325f69820251'
latitude = '40.6732'
longitude = '-73.991332'
f_url_template = 'http://farm%s.staticflickr.com/%s/%s_%s_%s.jpg'
imgs = []
infos = {}
f_api = FlickrAPI(api_key = api_key, api_secret = api_secret)
r_s = redis.Redis()

def make_img_url(photo):
	img = f_url_template % (photo['farm'], photo['server'], photo['id'], photo['secret'], 'm')
	imgs.append({'id': photo['id'], 'url': img})
	params = {}
	params['photo_id'] = photo['id']
	r = f_api.get('flickr.photos.getInfo', params)
	if(r['stat'] == 'ok'):
		#infos[photo['id']] = r
		latitude = str(r['photo']['location']['latitude'])
		longitude = str(r['photo']['location']['longitude'])
		photo_str = 'photo:' + photo['id']
		r_s.hset(photo_str, 'url', img)
		r_s.hset(photo_str, 'latitude', latitude)
		r_s.hset(photo_str, 'longitude', longitude)
	else:
		print "Could not retrieve photo info."

def main():
	params = {}
	params['lat'] = latitude
	params['lon'] = longitude
	r = f_api.get('flickr.photos.search', params)
	if(r['stat'] == 'ok'):
		for i in r['photos']['photo']:
			make_img_url(i)
	else:
		print "Could not retrieve photos."

if __name__ == "__main__":
	main()