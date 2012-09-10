<?php

/**
 * This is the model class for table "teacher_app".
 *
 * The followings are the available columns in table 'teacher_app':
 * @property integer $id
 * @property string $preferPlace
 * @property string $preferTime
 * @property string $courseID
 * @property string $name
 * @property string $teacherID
 * @property string $appTime
 * @property string $pass
 * @property string $teacherName
 */
class TeacherApp extends CActiveRecord
{
	/**
	 * Returns the static model of the specified AR class.
	 * @param string $className active record class name.
	 * @return TeacherApp the static model class
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
		return 'teacher_app';
	}

	public function setTeacherId(){
		$this->teacherID = Yii::app()->user->id;
	}
	
	public function setAppTime(){
		$this->appTime = date("Y-m-d H:i:s");
	}
	
	public function getCourseList($id)
        {
                $model = CourseBasicInfo::model()->findAllByAttributes(array('course_id'=>$id));
				
                //return CHtml::listData($model,'course_id', 'id', 'id');
				return array(
				'course_id'=>$model[0]->id,
				'name'=>$model[0]->name,
				);
        }
	
	protected function beforeSave() {
		 
		 //set course id
		 //$course = CourseBasicInfo::model()->getCourseList($this->courseID);
		 $course = $this->getCourseList($this->courseID);
		 $tempID = $this->courseID;
	     $this->courseID = $course['course_id'];
		 $this->name = $course['name'];


		 return parent::beforeSave();
	}
	
	/**
	 * @return array validation rules for model attributes.
	 */
	public function rules()
	{
		// NOTE: you should only define rules for those attributes that
		// will receive user inputs.
		return array(
			array('courseID', 'required'),
			array('id', 'numerical', 'integerOnly'=>true),
			array('preferPlace', 'length', 'max'=>9),
			array('preferTime, name', 'length', 'max'=>45),
			array('courseID, teacherID', 'length', 'max'=>11),
			// The following rule is used by search().
			// Please remove those attributes that should not be searched.
			array('id, preferPlace, preferTime, courseID, name, teacherID, appTime, pass', 'safe', 'on'=>'search'),
			
			//rules by jinrui
			array('courseID','courseIDValid'),
		);
	}

	/**
	 * if the courseID is valid
	 */
	public function courseIDValid($attribute, $params){
		if(!$this->hasErrors()){
			//$course = CourseBasicInfo::model()->getCourseList($this->courseID);
			
			$course = $this->getCourseList($this->courseID);
			//$this->addError('courseID', count($course));
			if(!$course['course_id']){
				$this->addError('courseID', Yii::t('courseArrangement','Course id does not exist!'));
			}
			
		}
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
		return array(
			'id' => 'ID',
			'preferPlace' => 'Prefer Place',
			'preferTime' => 'Prefer Time',
			'courseID' => 'Course ID',
			'name' => 'Name',
			'teacherID' => 'Teacher',
			'appTime' => 'App Time',
			'pass'=>'pass state'
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

		$criteria->compare('id',$this->id);
		$criteria->compare('preferPlace',$this->preferPlace,true);
		$criteria->compare('preferTime',$this->preferTime,true);
		$criteria->compare('courseID',$this->courseID,true);
		$criteria->compare('name',$this->name,true);
		$criteria->compare('teacherID',$this->teacherID,true);
		$criteria->compare('appTime',$this->appTime,true);
		$criteria->compare('pass',$this->pass,true);

		return new CActiveDataProvider($this, array(
			'criteria'=>$criteria,
		));
	}
}