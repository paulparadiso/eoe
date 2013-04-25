from flickr import FlickrAPI
from instagram.client import InstagramAPI
import redis

latitude = '40.6732'
longitude = '-73.991332'
f_url_template = 'http://farm%s.staticflickr.com/%s/%s_%s_%s.jpg'
imgs = []
infos = {}
api_key = '5c28f35a444332cbb9e19d15bbbffdf5'
api_secret = 'a631325f69820251'
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
		r_s.hset(photo_str, 'src', 'flickr')
	else:
		print "Could not retrieve photo info."

def make_image_url_inst(photo):
	i_url = photo.images['low_resolution'].url
	i_lat = photo.location.point.latitude
	i_lng = photo.location.point.longitude
	photo_str = 'photo:' + photo.id
	print "saving instagram image - " + photo.id
	r_s.hset(photo_str, 'url', i_url)
	r_s.hset(photo_str, 'latitude', i_lat)
	r_s.hset(photo_str, 'longitude', i_lng)
	r_s.hset(photo_str, 'src', 'instagram')

def download_flickr():
	params = {}
	params['lat'] = latitude
	params['lon'] = longitude
	params['per_page'] = 500;
	params['page'] = 1
	params['radius'] = 32;
	b_more_pages = True
	while(b_more_pages == True):
		print "getting flickr page - " + str(params['page'])
		r = f_api.get('flickr.photos.search', params)
		if(r['stat'] == 'ok'):
			#print r['photos']['total']
			#print r['photos']['perpage']
			#print r['photos']['pages']
			#print r['photos']['page']
			for i in r['photos']['photo']:
				make_img_url(i)
		else:
			print "Could not retrieve photos."
		num_pages = int(r['photos']['pages'])
		page = int(r['photos']['page'])
		if(num_pages - page <= 0):
			b_more_pages = False
		else:
			params['page'] = params['page'] + 1

def download_instagram():
	inst_client_id = '638009caa4e7485f91c3c07330448ae4'
	inst_client_secret = 'a79a36a7b7054ff192506263f30b6f58'
	inst_api = InstagramAPI(client_id = inst_client_id, client_secret = inst_client_secret)
	media = inst_api.media_search(lat = latitude, lng = longitude, distance = 5000, count = 10000)
	for i in media:
		make_image_url_inst(i)

def main():
	download_flickr()
	download_instagram()

if __name__ == "__main__":
	main()