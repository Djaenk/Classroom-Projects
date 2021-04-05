import React from 'react';
import {ProductReview} from '../models/ProductReview';
import {Rating} from './Rating';

export class ReviewForm extends React.Component{
	state = {
		name: '',
		rating: 0,
		comment: ''
	};

	onSubmission(){
		let date = new Date();
		this.props.addReview(new ProductReview(
			this.state.name,
			date.toDateString(),
			this.state.rating,
			this.state.comment
		));

		this.setState({
			name: '',
			rating: 0,
			comment: ''
		})
	};

	render(){
		return <form>
			<h4 id="form-header">Add Review</h4>
			<div id="name-input-group">
				<label htmlFor="name">Your Name</label>
				<input type="text" id="name-input" name="name" className="form-control" value={this.state.name} onChange={event => this.setState({name: event.target.value})}/>
			</div>
			<div id="rating-input-group">
				<label htmlFor="rating">Rating</label>
				<select id="rating-input" name="rating" className="form-control" value={this.state.rating} onChange={event => this.setState({rating: event.target.value})}>
					<option value="0"></option>
					<option value="1">1 star</option>
					<option value="2">2 stars</option>
					<option value="3">3 stars</option>
					<option value="4">4 stars</option>
					<option value="5">5 stars</option>
				</select>
				<Rating value={this.state.rating}/>
			</div>
			<div id="comment-input-group">
				<label htmlFor="comment">Comment</label>
				<textarea id="comment" name="comment" className="form-control" value={this.state.comment} onChange={event => this.setState({comment: event.target.value})}/>
			</div>
			<div id="submit-button-group">
				<button type="button" className="btn btn-primary" onClick={() => this.onSubmission()}>Submit</button>
			</div>
		</form>
	}
}