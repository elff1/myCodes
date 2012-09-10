<?php

/**
 * This is the model class for table "res_resource".
 *
 * The followings are the available columns in table 'res_resource':
 * @property string $id
 * @property string $path
 * @property string $display_name
 * @property string $uploader_id
 * @property string $download_count
 * @property string $resource_type
 * @property string $description
 * @property string $upload_time
 *
 * The followings are the available model relations:
 * @property ResAssignment[] $resAssignments
 * @property ResHomework[] $resHomeworks
 * @property UserAuthentication $uploader
 */
class ResResource extends CActiveRecord
{
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return ResResource the static model class
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
		return 'res_resource';
	}

	/**
	 * @return array validation rules for model attributes.
	 */
	public function rules()
	{
		// NOTE: you should only define rules for those attributes that
		// will receive user inputs.
		return array(
			array(/*'path, */'display_name, uploader_id, resource_type, description, upload_time', 'required'),
			array('path, display_name', 'length', 'max'=>255),
			array('uploader_id, download_count, resource_type', 'length', 'max'=>10),
			array('description', 'length', 'max'=>2048),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('id, path, display_name, uploader_id, download_count, resource_type, description, upload_time', 'safe', 'on'=>'search'),
			array('path', 'file', 'allowEmpty'=>true, 'types'=>'jpg,png,bmp,gif,doc,docx,ppt,pptx,xls,xlsx,txt,rar,zip,pdf', 'maxSize'=> 1024*1024*10, 'tooLarge'=>'File too large!Max File Size is 10MB!'),
			//plus, the maxsize may be effected by PHP config too.
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
			'resAssignments' => array(self::HAS_MANY, 'ResAssignment', 'resource_id'),
			'resHomeworks' => array(self::HAS_MANY, 'ResHomework', 'resource_id'),
			'uploader' => array(self::BELONGS_TO, 'UserAuthentication', 'uploader_id'),
		);
	}

	/**
	 * @return array customized attribute labels (name=>label)
	 */
	public function attributeLabels()
	{
		return array(
			'id' => ResourceModule::t('resResource','Resource ID'),
			'path' => ResourceModule::t('resResource','Path'),
			'display_name' => ResourceModule::t('resResource','Resource Name'),
			'uploader_id' => ResourceModule::t('resResource','Uploader'),
			'download_count' => ResourceModule::t('resResource','Download Count'),
			'resource_type' => ResourceModule::t('resResource','Resource Type'),
			'description' => ResourceModule::t('resResource','Resource Description'),
			'upload_time' => ResourceModule::t('resResource','Upload Time'),
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

		$criteria->compare('id',$this->id,true);
		$criteria->compare('path',$this->path,true);
		$criteria->compare('display_name',$this->display_name,true);
		$criteria->compare('uploader_id',$this->uploader_id,true);
		//$criteria->compare('download_count',$this->download_count,true);
		$criteria->compare('resource_type',$this->resource_type,true);
		$criteria->compare('description',$this->description,true);
		$criteria->compare('upload_time',$this->upload_time,true);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
	
	 public function behaviors() {
        return array(
            'commentable' => array(
                'class' => 'ext.comment-module.behaviors.CommentableBehavior',
                // name of the table created in last step
                'mapTable' => 'res_comments',
                // name of column to related model id in mapTable
                'mapRelatedColumn' => 'resId'
            ),
       );
	 }
}
