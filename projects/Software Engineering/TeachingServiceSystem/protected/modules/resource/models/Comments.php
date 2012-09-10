<?php

/**
 * This is the model class for table "comments".
 *
 * The followings are the available columns in table 'comments':
 * @property string $id
 * @property string $message
 * @property string $userId
 * @property string $createDate
 *
 * The followings are the available model relations:
 * @property UserAuthentication $user
 * @property ResComments[] $resComments
 */
class Comments extends CActiveRecord
{
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return Comments the static model class
	 */
	public static function model($className=__CLASS__)
	{
		return parent::model($className);
	}

	/**
	 * @return string the associated database table name
	 */
	public function tableName()
	{
		return 'comments';
	}

	/**
	 * @return array validation rules for model attributes.
	 */
	public function rules()
	{
		// NOTE: you should only define rules for those attributes that
		// will receive user inputs.
		return array(
			array('userId', 'length', 'max'=>11), //the max lenght of userID and length is 11
			array('message, createDate', 'safe'), //safe typefor message and createDate attributes
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('id, message, userId, createDate', 'safe', 'on'=>'search'), //use id, message, userID, createDate attributes for search
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
			'user' => array(self::BELONGS_TO, 'UserAuthentication', 'userId'),
			'resComments' => array(self::HAS_MANY, 'ResComments', 'commentId'), //one-to-many relation
		);
	}

	/**
	 * @return array customized attribute labels (name=>label)
	 */
	public function attributeLabels()
	{
		//map attributes to labels
		return array(
			'id' => 'ID',
			'message' => 'Message',
			'userId' => 'User',
			'createDate' => 'Create Date',
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
		//id, message, userID and createDate are involved in search
		$criteria->compare('id',$this->id,true);
		$criteria->compare('message',$this->message,true);
		$criteria->compare('userId',$this->userId,true);
		$criteria->compare('createDate',$this->createDate,true);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}