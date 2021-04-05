import React from 'react';
import {Product} from '../models/Product'
import {ReviewList} from './ReviewList'
import {ReviewForm} from './ReviewForm'

export class ProductDetails extends React.Component{
	state = {
		product: new Product(1, "Jif Peanut Butter, 40 ounce", "$5.99", "7g of Protein per serving with no preservative, artificial flavors or colors.", "https://johnlawrimore.com/smu/101.png", [])
	};

	addReview(review){
		let newProduct = this.state.product;
		newProduct.reviews.push(review);
		this.setState({
				product: newProduct
		})
	};

	render(){
		return <div id="product-details">
			<nav aria-label="breadcrumb">
				<ol className="breadcrumb">
					<li className="breadcrumb-item"><a href="#">Tasty Snacks</a></li>
					<li className="breadcrumb-item active">{this.state.product.name}</li>
				</ol>
			</nav>
			<div id="product" className="jumbotron">
				<img src={this.state.product.image} alt={this.state.product.name}></img>
				<div id="product-info">
					<h1 className="display-4">{this.state.product.name}</h1>
					<h2><span className="badge badge-primary">{this.state.product.price}</span></h2>
					<p className="lead">{this.state.product.description}</p>
				</div>
			</div>
			<ReviewList reviews={this.state.product.reviews}/>
			<ReviewForm addReview={review => this.addReview(review)}/>
		</div>;
	}
}