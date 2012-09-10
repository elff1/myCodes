<?php

/**
 * This is the model class for table "res_comments".
 *
 * The followings are the available columns in table 'res_comments':
 * @property string $resId
 * @property string $commentId
 */
class ResComments extends CActiveRecord
{
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return ResComments the static model class
	 */
	public static function model($className=__CLASS__)
	{
		return parent::model($className);
	}

	/**
	 * @return string the associated database table name
	 */
	//return associated table name
	public function tableName()
	{
		return 'res_comments';
	}

	/**
	 * @return array validation rules for model attributes.
	 */
	public function rules()
	{
		// NOTE: you should only define rules for those attributes that
		// will receive user inputs.
		return array(
			array('resId, commentId', 'required'), //resID and commentID attributes are essential
			array('resId, commentId', 'length', 'max'=>11), //the max length for resID and commentID is 11
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('resId, commentId', 'safe', 'on'=>'search'), //use resID and commentID for search
		);
	}

	/**
	 * @return array relational rules.
	 */
	public function relations()
	{
		// NOTE: you may need to adjust the relation name and the related
		// class name for the relations automatically generated below.
		return array(
		);
	}

	/**
	 * @return array customized attribute labels (name=>label)
	 */
	public function attributeLabels()
	{
		//map attribute names to labels
		return array(
			'resId' => 'Res',
			'commentId' => 'Comment',
		);
	}

	/**
	 * Retrieves a list of models based on the current search/filter conditions.
	 * @return CActiveDataProvider the data provider that can return the models based on the search/filter conditions.
	 */
	public function search()
	{
		// Warning: Please modify the following code to remove attributes that
		// should not be searched.

		$criteria=new CDbCriteria;
		//use resID and commentID as search criteria
		$criteria->compare('resId',$this->resId,true);
		$criteria->compare('commentId',$this->commentId,true);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}