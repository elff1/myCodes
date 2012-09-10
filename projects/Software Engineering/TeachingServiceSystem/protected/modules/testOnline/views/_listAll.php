<h1>Course List</h1>
<?php
$this->breadcrumbs=array(
		'OnlineTest Subsystem'=>array('/testOnline'),
		'Courses List',
);

if(AccountComponent::getUserSelectedType()===UserAuthentication::TYPE_STUDENT)
	$this->menu=array(
			array('label'=>TestOnlineModule::t('core','List taken Courses'), 'url'=>array('listTaken')),
	);
?>


<?php 
$this->widget('zii.widgets.grid.CGridView', array(
		'id'=>'list-all-grid',
		'dataProvider'=>CourseBasicInfo::model()->search(),
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