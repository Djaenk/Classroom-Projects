import React from 'react';
import {CartService} from '../services/CartService'

export const MyCart = props => {
	const cart = new CartService().getCart();

	return <>
		<table id="cart" className="table">
			<thead className="font-weight-bold">
				<th>Qty</th>
				<th>Name</th>
				<th>Total</th>
			</thead>
			<tbody>
			{
				cart.items.map(item =>
					<tr className="tableRow">
						<td>{item.quantity}</td>
						<td>{item.product.name} - <span className="text-secondary">${item.product.price}/each</span></td>
						<td>${item.totalPrice}</td>
					</tr>	
				)
			}
				<tr className="tableRow font-weight-bold">
					<td></td>
					<td></td>
					<td>${cart.total}</td>
				</tr>
			</tbody>
		</table>
	</>
}