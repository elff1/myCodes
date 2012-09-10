<?php

/**
 * This is the model class for table "program".
 *
 * The followings are the available columns in table 'program':
 * @property string $id
 * @property string $name
 * @property string $department_id
 * @property integer $length
 * @property string $grade
 * @property string $introduction
 *
 * The followings are the available model relations:
 * @property Department $department
 * @property ProgramDetail[] $programDetails
 * @property StudentBasicInfo[] $studentBasicInfos
 */
class Program extends CActiveRecord
{
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return Program the static model class
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
		return 'program';
	}
	
	protected function beforeSave() //fix the problem that ''->int will not be null.
	{
		if(empty($this->department_id)){
			$this->department_id=null;
		}
		return parent::beforeSave();
	}

	/**
	 * @return array validation rules for model attributes.
	 */
	//对应于数据表中的constraints，对数据的一些格式限定
	public function rules()
	{
		// NOTE: you should only define rules for those attributes that
		// will receive user inputs.
		return array(
			array('length', 'numerical', 'integerOnly'=>true),
			array('name', 'length', 'max'=>16),
			array('department_id', 'length', 'max'=>11),
			array('grade', 'length', 'max'=>4),
			array('introduction', 'length', 'max'=>2048),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('id, name, department_id, length, grade, introduction', 'safe', 'on'=>'search'),
			array('department_id', 'legalDepartment'),
		);
	}
	
	public function getProgramList(){
		$recordArray = $this->findAll();
		return CHtml::listData($recordArray,'id','name');
	}
	
	public function getLengthOptions(){//yy
		return array(4=>'四年',5=>'五年',8=>'八年',9=>'2+2',10=>'3+1');
	}
	
	
	//check that department_id is legal
	/**
 	 * @param string $attribute the name of the attribute to be validated
 	 * @param array $params options specified in the validation rule
 	 */
	public function legalDepartment($attribute, $params){
		if(!$this->hasErrors()){
			if(!empty($this->department_id)  &&  !Department::model()->findByPk($this->department_id)){
				$this->addError('department_id', InformationManagementModule::t('program','Invalid department ID.'));
			}
		}
	}
	

	/**
	 * @return array relational rules.
	 */
	//本Model对应的数据表的外键信息
	public function relations()
	{
		// NOTE: you may need to adjust the relation name and the related
		// class name for the relations automatically generated below.
		return array(
			'department' => array(self::BELONGS_TO, 'Department', 'department_id'),
			'programDetails' => array(self::HAS_MANY, 'ProgramDetail', 'program_id'),
			'studentBasicInfos' => array(self::HAS_MANY, 'StudentBasicInfo', 'program_id'),
		);
	}

	/**
	 * @return array customized attribute labels (name=>label)
	 */
	//变量在显示时的映射名称，用于翻译
	public function attributeLabels()
	{
		return array(
			'id' => 'ID',
			'name' => InformationManagementModule::t('program','Name'),
			'department_id' => InformationManagementModule::t('program','Department'),
			'length' => InformationManagementModule::t('program','Length'),
			'grade' => InformationManagementModule::t('program','Grade'),
			'introduction' => InformationManagementModule::t('program','Introduction'),
		);
	}

	/**
	 * Retrieves a list of models based on the current search/filter conditions.
	 * @return CActiveDataProvider the data provider that can return the models based on the search/filter conditions.
	 */
	//搜索时创建一个新的DataProvider
	//用于匹配用户的输入并筛选数据
	public function search()
	{
		// Warning: Please modify the following code to remove attributes that
		// should not be searched.

		$criteria=new CDbCriteria;

		$criteria->compare('id',$this->id,true);
		$criteria->compare('name',$this->name,true);
		$criteria->compare('department_id',$this->department_id,true);
		$criteria->compare('length',$this->length);
		$criteria->compare('grade',$this->grade,true);
		$criteria->compare('introduction',$this->introduction,true);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}