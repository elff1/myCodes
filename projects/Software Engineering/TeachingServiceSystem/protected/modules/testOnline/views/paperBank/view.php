<?php
// the breadcrumbs list
$this->breadcrumbs=array(
		'Online Test Subsystem'=>array('/testOnline'),
		'Course List'=>array('default/listCourses'),
		AccountComponent::getSelected_course_name()=>array('paperBank/'),
		$model->id,
);

// the menu list
if(AccountComponent::getUserType()===UserAuthentication::TYPE_STUDENT|AccountComponent::getUserSelectedType()===UserAuthentication::TYPE_STUDENT){
	$this->menu=array(
			array('label'=>TestOnlineModule::t('core','Take Online Test'), 'url'=>array('testRecording/')),
	);
}
else if($model->is_publish == 0) {
	$this->menu=array(
	 	array('label'=>'Modify Paper Information', 'url'=>array('update', 'id'=>$model->id)),
	 	array('label'=>'Auto Add Questions', 'url'=>array('goAutoAdd','id'=>$model->id)),
		array('label'=>'Modify Questions', 'url'=>array('paper/admin')),
//	 	array('label'=>'Delete Paper', 'url'=>'#', 'linkOptions'=>array('submit'=>array('delete','id'=>$model->id),'confirm'=>'Are you sure you want to delete this paper?')),

	);
}
?>

<!-- the title -->
<h1>View Paper<?php // echo $model->id; ?></h1>

<?php
// the paper information view
$this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		array(
			'name'=>'teacher_id',
			'value'=>CHtml::encode($model->teacher->getFullName())
		),
		array(
			'name'=>'course_id',
			'value'=>CHtml::encode(AccountComponent::getSelected_course_name())
		),
		array(
			'name'=>'is_publish',
			'value'=>CHtml::encode($model->getIsPublish())
		),
		'timelimit',
	),));

// $this->widget('zii.widgets.CListView', array(
// 	'dataProvider'=>TestInfoComponent::getQuestionByPaper($model->id),
// 	'itemView'=>'_question_view',
// ));

// the paper question list view
$this->widget('zii.widgets.grid.CGridView', array(
	'id'=>'question-bank-grid',
	'dataProvider'=>TestInfoComponent::getQuestionByPaper($model->id),
	'filter'=>QuestionBank::model(),

	'columns'=>array(
		'id',
		'question',
		'selection_a',
		'selection_b',
		'selection_c',
		'selection_d',
		'type',
		'answer',
	),
));

 ?>
