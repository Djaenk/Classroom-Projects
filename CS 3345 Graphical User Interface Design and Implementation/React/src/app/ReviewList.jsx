import React from 'react';
import {Rating} from './Rating';

export const ReviewList = props =>
	<ul className="list-group">
		<h4>Product Reviews <span className="review-count">({props.reviews.length})</span></h4>
		{!props.reviews.length ? 
			<p id="review-placeholder">Be the first to add a review!</p>
			:
			props.reviews.map((review, i) =>
				<li className="review" key={i}>
					<div className="review-header"><Rating value={review.rating}/></div>
					<div className="review-date">{review.date}</div>
					<div className="review-name">{review.name}</div>
					<div className="review-comment">"{review.comment}"</div>
				</li>)
		}
	</ul>