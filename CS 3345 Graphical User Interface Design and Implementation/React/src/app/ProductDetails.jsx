import React from 'react';
import {ReviewList} from './ReviewList'
import {ReviewForm} from './ReviewForm'
import { ProductRepository } from '../api/ProductRepository';
import CartService from '../services/CartService';
import { Link } from 'react-router-dom';

export class ProductDetails extends React.Component{
	repo = new ProductRepository();
	cart = new CartService();
	productId;

	state = {
		product: undefined
	};

	addReview(review){
		this.repo.addReview(this.productId, review);
	};

	render(){
		if(!this.state.product){
			return <div id="product-details">Loading...</div>
		}
		return <div id="product-details">
			<nav aria-label="breadcrumb">
				<ol className="breadcrumb">
					<li className="breadcrumb-item"><Link to='/'>Tasty Snacks</Link></li>
					<li className="breadcrumb-item">{this.state.product.name}</li>
				</ol>
			</nav>
			<div id="product" className="jumbotron">
				<img src={this.state.product.imageUrl} alt={this.state.product.name}></img>
				<div id="product-info">
					<h1 className="display-4">{this.state.product.name}</h1>
					<h2><span className="badge badge-primary">{this.state.product.price}</span></h2>
					<p className="lead">{this.state.product.description}</p>
				</div>
			</div>
			<Link to={`/cart`} className="btn btn-warning add-cart" onClick={() => this.cart.addToCart(this.state.product)}>Add to Cart</Link>
			<ReviewList reviews={this.state.product.reviews}/>
			<ReviewForm addReview={review => this.addReview(review)}/>
		</div>;
	}

	componentWillMount(){
		this.productId = this.props.match.params.productId;
	}

	componentDidMount(){
		this.repo.getProduct(this.productId).then(product =>
			this.setState({product: product})
		)
	}

	componentDidUpdate(){
		this.repo.getProduct(this.productId).then(product =>
			this.setState({product: product})
		)
	}
}