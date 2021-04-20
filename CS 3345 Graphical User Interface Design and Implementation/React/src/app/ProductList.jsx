import React, {useEffect, useState} from 'react';
import {ProductRepository} from '../api/ProductRepository';
import {Link} from 'react-router-dom';
import CartService from '../services/CartService';

export const ProductList = props => {
	const [products, setProducts] = useState([]);
	const productRepo = new ProductRepository();
	const cart = new CartService();

	useEffect(() => {
		productRepo.getProducts().then(
			resp => {
				setProducts(resp);
			}
		)
	}, []);

	return <div id="product-list">
		<nav aria-label="breadcrumb">
			<ol className="breadcrumb">
				<li className="breadcrumb-item">Tasty Snacks</li>
			</ol>
		</nav>

		<div id="product-list" className="row">
		{
			products.map(product =>
				<div key={product.id} className="card col">
					<div className="card-body">
						<img className="card-img" src={product.imageUrl} alt={product.name}/>
						<div className="badge badge-success rounded-pill position-absolute product-price">{product.price}</div>
						<h4 className="text-center card-title product-name">{product.name}</h4>
						<Link to={`/products/${product.id}`} className="btn btn-info btn-block">Product Details</Link>
						<Link to={`/cart`} className="btn btn-warning btn-block" onClick={() => cart.addToCart(product)}>Add to Cart</Link>
					</div>
				</div>)
		}
		</div>
	</div>
}