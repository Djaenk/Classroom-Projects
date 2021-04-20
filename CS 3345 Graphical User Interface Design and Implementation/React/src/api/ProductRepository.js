import axios from 'axios';

export class ProductRepository{
	url = 'https://api.johnlawrimore.com/store/products'

	config = {
		headers: {
			Authorization: 'awang'
		}
	};

	getProducts(){
		return new Promise((resolve, reject) => {
			axios.get(`${this.url}/`, this.config)
				.then(x => resolve(x.data))
				.catch(error => {
					alert(error);
					reject(error);
				});
		})
	}

	getProduct(productId){
		return new Promise((resolve, reject) => {
			axios.get(`${this.url}/${productId}`, this.config)
				.then(x => resolve(x.data))
				.catch(error => {
					alert(error);
					reject(error);
				});
		})
	}

	addReview(productId, review){
		console.log(productId);
		console.log(review);
		return new Promise((resolve, reject) => {
			axios.post(`${this.url}/${productId}/reviews`, review, this.config)
				.then(x => resolve(x.data))
				.catch(error => {
					alert(error);
					reject(error);
				});
		})
	}
}