<?php

/**
 * TeacherBasicInfoBatchForm class.
 * TeacherBasicInfoBatchForm is the data structure for keeping
 * teacher basic info batch import form data. It is used by the 'batchCreate' action of 'TeacherBasicInfoController'.
 */
class TeacherBasicInfoBatchForm extends CFormModel
{
	public $file;
	
	/**
	 * Declares the validation rules.
	 * The rules state that username and password are required,
	 * and password needs to be authenticated.
	 */
	//对应于数据表中的constraints，对数据的一些格式限定
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
	//变量在显示时的映射名称，用于翻译
	public function attributeLabels()
	{
		return array(
			'file'=>InformationManagementModule::t('teacherBasicInfo','Teacher Basic Info File'),
		);
	}
}
