<h1>Course List</h1>
<?php
$this->breadcrumbs=array(
		'OnlineTest Subsystem'=>array('/testOnline'),
		'Courses List',
);

if(AccountComponent::getUserSelectedType()===UserAuthentication::TYPE_STUDENT)
	$this->menu=array(
			array('label'=>TestOnlineModule::t('core','List all Courses'), 'url'=>array('listAll')),
	);
	?>

<?php 
if(AccountComponent::getUserType()===UserAuthentication::TYPE_TEACHER|AccountComponent::getUserType()===UserAuthentication::TYPE_STUDENT)
	$this->widget('zii.widgets.CListView', array(
			'dataProvider'=>AccountComponent::getCourses(),
			'itemView'=>'/_coursesView',
	));
else
	$this->widget('zii.widgets.grid.CGridView', array(
			'id'=>'list-courses-grid',
			'dataProvider'=>AccountComponent::getCourses(),
			'filter'=>CourseBasicInfo::model(),
			'columns'=>array(
					'course_id',
					'name',
					'introduction',
					array('class'=>'CButtonColumn', 'template'=>'{view}',
					'buttons'=>array(
						'view' => array(
								'url'=>'Yii::app()->createUrl("testOnline/default/updateSelectedCourse",array("course_id"=>$data->id))',
						),
					)
			),
			),
	));
?>