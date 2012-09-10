<?php

/**
 * ContactForm class.
 * ContactForm is the data structure for keeping
 * contact form data. It is used by the 'contact' action of 'SiteController'.
 */
class AutoAdd extends CFormModel
{
	/**
	 * the number of the problems to be auto-generated
	 */
	public $number;

	/**
	 * Declares the validation rules.
	 */
	public function rules()
	{
		return array(
			// number are required and as numerical
			array('number', 'required'),
			array('number', 'numerical'),
		);
	}

	/**
	 * Declares customized attribute labels.
	 * If not declared here, an attribute would have a label that is
	 * the same as its name with the first letter in upper case.
	 */
	public function attributeLabels()
	{
		return array(
			'number'=>'Number of Problems',
		);
	}
}