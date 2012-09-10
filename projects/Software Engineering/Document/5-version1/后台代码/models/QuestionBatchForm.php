<?php

/**
 * QuestionBatchForm class.
 */
class QuestionBatchForm extends CFormModel
{
	public $file;
	
	/**
	 * Declares the validation rules.
	 */
	public function rules()
	{
		return array(
			// username and password are required
			array('file', 'file', 'types'=>'csv', 'maxSize'=>Yii::app()->params['maxBatchCreateFileSize']),
		);
	} 

	/**
	 * Declares attribute labels.
	 */
	public function attributeLabels()
	{
		return array(
			'file'=>TestOnlineModule::t('Questions','Questions Content File'),
		);
	}
}
