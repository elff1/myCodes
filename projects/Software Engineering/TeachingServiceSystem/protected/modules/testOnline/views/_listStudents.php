
<h1>Student List</h1>
<?php
$this->breadcrumbs=array(
	'OnlineTest Subsystem',
);
?>
<?php 
$this->widget('zii.widgets.grid.CGridView', array(
			'id'=>'list-student-grid',
			'dataProvider'=>AccountComponent::getStudentList(),
			'filter'=>StudentBasicInfo::model(),
			'columns'=>array(
					'student_id',
					'current_grade',
					'class_id',
					array('class'=>'CButtonColumn', 'template'=>'{view}',
					'buttons'=>array(
						'view' => array(
								'url'=>'Yii::app()->createUrl("testOnline/default/updateSelectedStudent",array("student_id"=>$data->id))',
						),
					)
			),
			),
	));
?>